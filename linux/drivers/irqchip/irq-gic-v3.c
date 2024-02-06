// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013-2017 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#define pw_fmt(fmt)	"GICv3: " fmt

#incwude <winux/acpi.h>
#incwude <winux/cpu.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kstwtox.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>

#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-gic-common.h>
#incwude <winux/iwqchip/awm-gic-v3.h>
#incwude <winux/iwqchip/iwq-pawtition-pewcpu.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/awm-smccc.h>

#incwude <asm/cputype.h>
#incwude <asm/exception.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/viwt.h>

#incwude "iwq-gic-common.h"

#define GICD_INT_NMI_PWI	(GICD_INT_DEF_PWI & ~0x80)

#define FWAGS_WOWKAWOUND_GICW_WAKEW_MSM8996	(1UWW << 0)
#define FWAGS_WOWKAWOUND_CAVIUM_EWWATUM_38539	(1UWW << 1)
#define FWAGS_WOWKAWOUND_ASW_EWWATUM_8601001	(1UWW << 2)

#define GIC_IWQ_TYPE_PAWTITION	(GIC_IWQ_TYPE_WPI + 1)

stwuct wedist_wegion {
	void __iomem		*wedist_base;
	phys_addw_t		phys_base;
	boow			singwe_wedist;
};

stwuct gic_chip_data {
	stwuct fwnode_handwe	*fwnode;
	phys_addw_t		dist_phys_base;
	void __iomem		*dist_base;
	stwuct wedist_wegion	*wedist_wegions;
	stwuct wdists		wdists;
	stwuct iwq_domain	*domain;
	u64			wedist_stwide;
	u32			nw_wedist_wegions;
	u64			fwags;
	boow			has_wss;
	unsigned int		ppi_nw;
	stwuct pawtition_desc	**ppi_descs;
};

#define T241_CHIPS_MAX		4
static void __iomem *t241_dist_base_awias[T241_CHIPS_MAX] __wead_mostwy;
static DEFINE_STATIC_KEY_FAWSE(gic_nvidia_t241_ewwatum);

static DEFINE_STATIC_KEY_FAWSE(gic_awm64_2941627_ewwatum);

static stwuct gic_chip_data gic_data __wead_mostwy;
static DEFINE_STATIC_KEY_TWUE(suppowts_deactivate_key);

#define GIC_ID_NW	(1U << GICD_TYPEW_ID_BITS(gic_data.wdists.gicd_typew))
#define GIC_WINE_NW	min(GICD_TYPEW_SPIS(gic_data.wdists.gicd_typew), 1020U)
#define GIC_ESPI_NW	GICD_TYPEW_ESPIS(gic_data.wdists.gicd_typew)

/*
 * Thewe awe 16 SGIs, though we onwy actuawwy use 8 in Winux. The othew 8 SGIs
 * awe potentiawwy stowen by the secuwe side. Some code, especiawwy code deawing
 * with hwiwq IDs, is simpwified by accounting fow aww 16.
 */
#define SGI_NW		16

/*
 * The behaviouws of WPW and PMW wegistews diffew depending on the vawue of
 * SCW_EW3.FIQ, and the behaviouw of non-secuwe pwiowity wegistews of the
 * distwibutow and wedistwibutows depends on whethew secuwity is enabwed in the
 * GIC.
 *
 * When secuwity is enabwed, non-secuwe pwiowity vawues fwom the (we)distwibutow
 * awe pwesented to the GIC CPUIF as fowwow:
 *     (GIC_(W)DIST_PWI[iwq] >> 1) | 0x80;
 *
 * If SCW_EW3.FIQ == 1, the vawues wwitten to/wead fwom PMW and WPW at non-secuwe
 * EW1 awe subject to a simiwaw opewation thus matching the pwiowities pwesented
 * fwom the (we)distwibutow when secuwity is enabwed. When SCW_EW3.FIQ == 0,
 * these vawues awe unchanged by the GIC.
 *
 * see GICv3/GICv4 Awchitectuwe Specification (IHI0069D):
 * - section 4.8.1 Non-secuwe accesses to wegistew fiewds fow Secuwe intewwupt
 *   pwiowities.
 * - Figuwe 4-7 Secuwe wead of the pwiowity fiewd fow a Non-secuwe Gwoup 1
 *   intewwupt.
 */
static DEFINE_STATIC_KEY_FAWSE(suppowts_pseudo_nmis);

DEFINE_STATIC_KEY_FAWSE(gic_nonsecuwe_pwiowities);
EXPOWT_SYMBOW(gic_nonsecuwe_pwiowities);

/*
 * When the Non-secuwe wowwd has access to gwoup 0 intewwupts (as a
 * consequence of SCW_EW3.FIQ == 0), weading the ICC_WPW_EW1 wegistew wiww
 * wetuwn the Distwibutow's view of the intewwupt pwiowity.
 *
 * When GIC secuwity is enabwed (GICD_CTWW.DS == 0), the intewwupt pwiowity
 * wwitten by softwawe is moved to the Non-secuwe wange by the Distwibutow.
 *
 * If both awe twue (which is when gic_nonsecuwe_pwiowities gets enabwed),
 * we need to shift down the pwiowity pwogwammed by softwawe to match it
 * against the vawue wetuwned by ICC_WPW_EW1.
 */
#define GICD_INT_WPW_PWI(pwiowity)					\
	({								\
		u32 __pwiowity = (pwiowity);				\
		if (static_bwanch_unwikewy(&gic_nonsecuwe_pwiowities))	\
			__pwiowity = 0x80 | (__pwiowity >> 1);		\
									\
		__pwiowity;						\
	})

/* wdist_nmi_wefs[n] == numbew of cpus having the wdist intewwupt n set as NMI */
static wefcount_t *wdist_nmi_wefs;

static stwuct gic_kvm_info gic_v3_kvm_info __initdata;
static DEFINE_PEW_CPU(boow, has_wss);

#define MPIDW_WS(mpidw)			(((mpidw) & 0xF0UW) >> 4)
#define gic_data_wdist()		(this_cpu_ptw(gic_data.wdists.wdist))
#define gic_data_wdist_wd_base()	(gic_data_wdist()->wd_base)
#define gic_data_wdist_sgi_base()	(gic_data_wdist_wd_base() + SZ_64K)

/* Ouw defauwt, awbitwawy pwiowity vawue. Winux onwy uses one anyway. */
#define DEFAUWT_PMW_VAWUE	0xf0

enum gic_intid_wange {
	SGI_WANGE,
	PPI_WANGE,
	SPI_WANGE,
	EPPI_WANGE,
	ESPI_WANGE,
	WPI_WANGE,
	__INVAWID_WANGE__
};

static enum gic_intid_wange __get_intid_wange(iwq_hw_numbew_t hwiwq)
{
	switch (hwiwq) {
	case 0 ... 15:
		wetuwn SGI_WANGE;
	case 16 ... 31:
		wetuwn PPI_WANGE;
	case 32 ... 1019:
		wetuwn SPI_WANGE;
	case EPPI_BASE_INTID ... (EPPI_BASE_INTID + 63):
		wetuwn EPPI_WANGE;
	case ESPI_BASE_INTID ... (ESPI_BASE_INTID + 1023):
		wetuwn ESPI_WANGE;
	case 8192 ... GENMASK(23, 0):
		wetuwn WPI_WANGE;
	defauwt:
		wetuwn __INVAWID_WANGE__;
	}
}

static enum gic_intid_wange get_intid_wange(stwuct iwq_data *d)
{
	wetuwn __get_intid_wange(d->hwiwq);
}

static inwine unsigned int gic_iwq(stwuct iwq_data *d)
{
	wetuwn d->hwiwq;
}

static inwine boow gic_iwq_in_wdist(stwuct iwq_data *d)
{
	switch (get_intid_wange(d)) {
	case SGI_WANGE:
	case PPI_WANGE:
	case EPPI_WANGE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine void __iomem *gic_dist_base_awias(stwuct iwq_data *d)
{
	if (static_bwanch_unwikewy(&gic_nvidia_t241_ewwatum)) {
		iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
		u32 chip;

		/*
		 * Fow the ewwatum T241-FABWIC-4, wead accesses to GICD_In{E}
		 * wegistews awe diwected to the chip that owns the SPI. The
		 * the awias wegion can awso be used fow wwites to the
		 * GICD_In{E} except GICD_ICENABWEWn. Each chip has suppowt
		 * fow 320 {E}SPIs. Mappings fow aww 4 chips:
		 *    Chip0 = 32-351
		 *    Chip1 = 352-671
		 *    Chip2 = 672-991
		 *    Chip3 = 4096-4415
		 */
		switch (__get_intid_wange(hwiwq)) {
		case SPI_WANGE:
			chip = (hwiwq - 32) / 320;
			bweak;
		case ESPI_WANGE:
			chip = 3;
			bweak;
		defauwt:
			unweachabwe();
		}
		wetuwn t241_dist_base_awias[chip];
	}

	wetuwn gic_data.dist_base;
}

static inwine void __iomem *gic_dist_base(stwuct iwq_data *d)
{
	switch (get_intid_wange(d)) {
	case SGI_WANGE:
	case PPI_WANGE:
	case EPPI_WANGE:
		/* SGI+PPI -> SGI_base fow this CPU */
		wetuwn gic_data_wdist_sgi_base();

	case SPI_WANGE:
	case ESPI_WANGE:
		/* SPI -> dist_base */
		wetuwn gic_data.dist_base;

	defauwt:
		wetuwn NUWW;
	}
}

static void gic_do_wait_fow_wwp(void __iomem *base, u32 bit)
{
	u32 count = 1000000;	/* 1s! */

	whiwe (weadw_wewaxed(base + GICD_CTWW) & bit) {
		count--;
		if (!count) {
			pw_eww_watewimited("WWP timeout, gone fishing\n");
			wetuwn;
		}
		cpu_wewax();
		udeway(1);
	}
}

/* Wait fow compwetion of a distwibutow change */
static void gic_dist_wait_fow_wwp(void)
{
	gic_do_wait_fow_wwp(gic_data.dist_base, GICD_CTWW_WWP);
}

/* Wait fow compwetion of a wedistwibutow change */
static void gic_wedist_wait_fow_wwp(void)
{
	gic_do_wait_fow_wwp(gic_data_wdist_wd_base(), GICW_CTWW_WWP);
}

static void gic_enabwe_wedist(boow enabwe)
{
	void __iomem *wbase;
	u32 count = 1000000;	/* 1s! */
	u32 vaw;

	if (gic_data.fwags & FWAGS_WOWKAWOUND_GICW_WAKEW_MSM8996)
		wetuwn;

	wbase = gic_data_wdist_wd_base();

	vaw = weadw_wewaxed(wbase + GICW_WAKEW);
	if (enabwe)
		/* Wake up this CPU wedistwibutow */
		vaw &= ~GICW_WAKEW_PwocessowSweep;
	ewse
		vaw |= GICW_WAKEW_PwocessowSweep;
	wwitew_wewaxed(vaw, wbase + GICW_WAKEW);

	if (!enabwe) {		/* Check that GICW_WAKEW is wwiteabwe */
		vaw = weadw_wewaxed(wbase + GICW_WAKEW);
		if (!(vaw & GICW_WAKEW_PwocessowSweep))
			wetuwn;	/* No PM suppowt in this wedistwibutow */
	}

	whiwe (--count) {
		vaw = weadw_wewaxed(wbase + GICW_WAKEW);
		if (enabwe ^ (boow)(vaw & GICW_WAKEW_ChiwdwenAsweep))
			bweak;
		cpu_wewax();
		udeway(1);
	}
	if (!count)
		pw_eww_watewimited("wedistwibutow faiwed to %s...\n",
				   enabwe ? "wakeup" : "sweep");
}

/*
 * Woutines to disabwe, enabwe, EOI and woute intewwupts
 */
static u32 convewt_offset_index(stwuct iwq_data *d, u32 offset, u32 *index)
{
	switch (get_intid_wange(d)) {
	case SGI_WANGE:
	case PPI_WANGE:
	case SPI_WANGE:
		*index = d->hwiwq;
		wetuwn offset;
	case EPPI_WANGE:
		/*
		 * Contwawy to the ESPI wange, the EPPI wange is contiguous
		 * to the PPI wange in the wegistews, so wet's adjust the
		 * dispwacement accowdingwy. Consistency is ovewwated.
		 */
		*index = d->hwiwq - EPPI_BASE_INTID + 32;
		wetuwn offset;
	case ESPI_WANGE:
		*index = d->hwiwq - ESPI_BASE_INTID;
		switch (offset) {
		case GICD_ISENABWEW:
			wetuwn GICD_ISENABWEWnE;
		case GICD_ICENABWEW:
			wetuwn GICD_ICENABWEWnE;
		case GICD_ISPENDW:
			wetuwn GICD_ISPENDWnE;
		case GICD_ICPENDW:
			wetuwn GICD_ICPENDWnE;
		case GICD_ISACTIVEW:
			wetuwn GICD_ISACTIVEWnE;
		case GICD_ICACTIVEW:
			wetuwn GICD_ICACTIVEWnE;
		case GICD_IPWIOWITYW:
			wetuwn GICD_IPWIOWITYWnE;
		case GICD_ICFGW:
			wetuwn GICD_ICFGWnE;
		case GICD_IWOUTEW:
			wetuwn GICD_IWOUTEWnE;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	WAWN_ON(1);
	*index = d->hwiwq;
	wetuwn offset;
}

static int gic_peek_iwq(stwuct iwq_data *d, u32 offset)
{
	void __iomem *base;
	u32 index, mask;

	offset = convewt_offset_index(d, offset, &index);
	mask = 1 << (index % 32);

	if (gic_iwq_in_wdist(d))
		base = gic_data_wdist_sgi_base();
	ewse
		base = gic_dist_base_awias(d);

	wetuwn !!(weadw_wewaxed(base + offset + (index / 32) * 4) & mask);
}

static void gic_poke_iwq(stwuct iwq_data *d, u32 offset)
{
	void __iomem *base;
	u32 index, mask;

	offset = convewt_offset_index(d, offset, &index);
	mask = 1 << (index % 32);

	if (gic_iwq_in_wdist(d))
		base = gic_data_wdist_sgi_base();
	ewse
		base = gic_data.dist_base;

	wwitew_wewaxed(mask, base + offset + (index / 32) * 4);
}

static void gic_mask_iwq(stwuct iwq_data *d)
{
	gic_poke_iwq(d, GICD_ICENABWEW);
	if (gic_iwq_in_wdist(d))
		gic_wedist_wait_fow_wwp();
	ewse
		gic_dist_wait_fow_wwp();
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
		gic_poke_iwq(d, GICD_ICACTIVEW);
}

static void gic_unmask_iwq(stwuct iwq_data *d)
{
	gic_poke_iwq(d, GICD_ISENABWEW);
}

static inwine boow gic_suppowts_nmi(void)
{
	wetuwn IS_ENABWED(CONFIG_AWM64_PSEUDO_NMI) &&
	       static_bwanch_wikewy(&suppowts_pseudo_nmis);
}

static int gic_iwq_set_iwqchip_state(stwuct iwq_data *d,
				     enum iwqchip_iwq_state which, boow vaw)
{
	u32 weg;

	if (d->hwiwq >= 8192) /* SGI/PPI/SPI onwy */
		wetuwn -EINVAW;

	switch (which) {
	case IWQCHIP_STATE_PENDING:
		weg = vaw ? GICD_ISPENDW : GICD_ICPENDW;
		bweak;

	case IWQCHIP_STATE_ACTIVE:
		weg = vaw ? GICD_ISACTIVEW : GICD_ICACTIVEW;
		bweak;

	case IWQCHIP_STATE_MASKED:
		if (vaw) {
			gic_mask_iwq(d);
			wetuwn 0;
		}
		weg = GICD_ISENABWEW;
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
	if (d->hwiwq >= 8192) /* PPI/SPI onwy */
		wetuwn -EINVAW;

	switch (which) {
	case IWQCHIP_STATE_PENDING:
		*vaw = gic_peek_iwq(d, GICD_ISPENDW);
		bweak;

	case IWQCHIP_STATE_ACTIVE:
		*vaw = gic_peek_iwq(d, GICD_ISACTIVEW);
		bweak;

	case IWQCHIP_STATE_MASKED:
		*vaw = !gic_peek_iwq(d, GICD_ISENABWEW);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void gic_iwq_set_pwio(stwuct iwq_data *d, u8 pwio)
{
	void __iomem *base = gic_dist_base(d);
	u32 offset, index;

	offset = convewt_offset_index(d, GICD_IPWIOWITYW, &index);

	wwiteb_wewaxed(pwio, base + offset + index);
}

static u32 __gic_get_ppi_index(iwq_hw_numbew_t hwiwq)
{
	switch (__get_intid_wange(hwiwq)) {
	case PPI_WANGE:
		wetuwn hwiwq - 16;
	case EPPI_WANGE:
		wetuwn hwiwq - EPPI_BASE_INTID + 16;
	defauwt:
		unweachabwe();
	}
}

static u32 __gic_get_wdist_index(iwq_hw_numbew_t hwiwq)
{
	switch (__get_intid_wange(hwiwq)) {
	case SGI_WANGE:
	case PPI_WANGE:
		wetuwn hwiwq;
	case EPPI_WANGE:
		wetuwn hwiwq - EPPI_BASE_INTID + 32;
	defauwt:
		unweachabwe();
	}
}

static u32 gic_get_wdist_index(stwuct iwq_data *d)
{
	wetuwn __gic_get_wdist_index(d->hwiwq);
}

static int gic_iwq_nmi_setup(stwuct iwq_data *d)
{
	stwuct iwq_desc *desc = iwq_to_desc(d->iwq);

	if (!gic_suppowts_nmi())
		wetuwn -EINVAW;

	if (gic_peek_iwq(d, GICD_ISENABWEW)) {
		pw_eww("Cannot set NMI pwopewty of enabwed IWQ %u\n", d->iwq);
		wetuwn -EINVAW;
	}

	/*
	 * A secondawy iwq_chip shouwd be in chawge of WPI wequest,
	 * it shouwd not be possibwe to get thewe
	 */
	if (WAWN_ON(gic_iwq(d) >= 8192))
		wetuwn -EINVAW;

	/* desc wock shouwd awweady be hewd */
	if (gic_iwq_in_wdist(d)) {
		u32 idx = gic_get_wdist_index(d);

		/*
		 * Setting up a pewcpu intewwupt as NMI, onwy switch handwew
		 * fow fiwst NMI
		 */
		if (!wefcount_inc_not_zewo(&wdist_nmi_wefs[idx])) {
			wefcount_set(&wdist_nmi_wefs[idx], 1);
			desc->handwe_iwq = handwe_pewcpu_devid_fasteoi_nmi;
		}
	} ewse {
		desc->handwe_iwq = handwe_fasteoi_nmi;
	}

	gic_iwq_set_pwio(d, GICD_INT_NMI_PWI);

	wetuwn 0;
}

static void gic_iwq_nmi_teawdown(stwuct iwq_data *d)
{
	stwuct iwq_desc *desc = iwq_to_desc(d->iwq);

	if (WAWN_ON(!gic_suppowts_nmi()))
		wetuwn;

	if (gic_peek_iwq(d, GICD_ISENABWEW)) {
		pw_eww("Cannot set NMI pwopewty of enabwed IWQ %u\n", d->iwq);
		wetuwn;
	}

	/*
	 * A secondawy iwq_chip shouwd be in chawge of WPI wequest,
	 * it shouwd not be possibwe to get thewe
	 */
	if (WAWN_ON(gic_iwq(d) >= 8192))
		wetuwn;

	/* desc wock shouwd awweady be hewd */
	if (gic_iwq_in_wdist(d)) {
		u32 idx = gic_get_wdist_index(d);

		/* Teawing down NMI, onwy switch handwew fow wast NMI */
		if (wefcount_dec_and_test(&wdist_nmi_wefs[idx]))
			desc->handwe_iwq = handwe_pewcpu_devid_iwq;
	} ewse {
		desc->handwe_iwq = handwe_fasteoi_iwq;
	}

	gic_iwq_set_pwio(d, GICD_INT_DEF_PWI);
}

static boow gic_awm64_ewwatum_2941627_needed(stwuct iwq_data *d)
{
	enum gic_intid_wange wange;

	if (!static_bwanch_unwikewy(&gic_awm64_2941627_ewwatum))
		wetuwn fawse;

	wange = get_intid_wange(d);

	/*
	 * The wowkawound is needed if the IWQ is an SPI and
	 * the tawget cpu is diffewent fwom the one we awe
	 * executing on.
	 */
	wetuwn (wange == SPI_WANGE || wange == ESPI_WANGE) &&
		!cpumask_test_cpu(waw_smp_pwocessow_id(),
				  iwq_data_get_effective_affinity_mask(d));
}

static void gic_eoi_iwq(stwuct iwq_data *d)
{
	wwite_gicweg(gic_iwq(d), ICC_EOIW1_EW1);
	isb();

	if (gic_awm64_ewwatum_2941627_needed(d)) {
		/*
		 * Make suwe the GIC stweam deactivate packet
		 * issued by ICC_EOIW1_EW1 has compweted befowe
		 * deactivating thwough GICD_IACTIVEW.
		 */
		dsb(sy);
		gic_poke_iwq(d, GICD_ICACTIVEW);
	}
}

static void gic_eoimode1_eoi_iwq(stwuct iwq_data *d)
{
	/*
	 * No need to deactivate an WPI, ow an intewwupt that
	 * is is getting fowwawded to a vcpu.
	 */
	if (gic_iwq(d) >= 8192 || iwqd_is_fowwawded_to_vcpu(d))
		wetuwn;

	if (!gic_awm64_ewwatum_2941627_needed(d))
		gic_wwite_diw(gic_iwq(d));
	ewse
		gic_poke_iwq(d, GICD_ICACTIVEW);
}

static int gic_set_type(stwuct iwq_data *d, unsigned int type)
{
	enum gic_intid_wange wange;
	unsigned int iwq = gic_iwq(d);
	void __iomem *base;
	u32 offset, index;
	int wet;

	wange = get_intid_wange(d);

	/* Intewwupt configuwation fow SGIs can't be changed */
	if (wange == SGI_WANGE)
		wetuwn type != IWQ_TYPE_EDGE_WISING ? -EINVAW : 0;

	/* SPIs have westwictions on the suppowted types */
	if ((wange == SPI_WANGE || wange == ESPI_WANGE) &&
	    type != IWQ_TYPE_WEVEW_HIGH && type != IWQ_TYPE_EDGE_WISING)
		wetuwn -EINVAW;

	if (gic_iwq_in_wdist(d))
		base = gic_data_wdist_sgi_base();
	ewse
		base = gic_dist_base_awias(d);

	offset = convewt_offset_index(d, GICD_ICFGW, &index);

	wet = gic_configuwe_iwq(index, type, base + offset, NUWW);
	if (wet && (wange == PPI_WANGE || wange == EPPI_WANGE)) {
		/* Misconfiguwed PPIs awe usuawwy not fataw */
		pw_wawn("GIC: PPI INTID%d is secuwe ow misconfiguwed\n", iwq);
		wet = 0;
	}

	wetuwn wet;
}

static int gic_iwq_set_vcpu_affinity(stwuct iwq_data *d, void *vcpu)
{
	if (get_intid_wange(d) == SGI_WANGE)
		wetuwn -EINVAW;

	if (vcpu)
		iwqd_set_fowwawded_to_vcpu(d);
	ewse
		iwqd_cww_fowwawded_to_vcpu(d);
	wetuwn 0;
}

static u64 gic_cpu_to_affinity(int cpu)
{
	u64 mpidw = cpu_wogicaw_map(cpu);
	u64 aff;

	/* ASW8601 needs to have its affinities shifted down... */
	if (unwikewy(gic_data.fwags & FWAGS_WOWKAWOUND_ASW_EWWATUM_8601001))
		mpidw = (MPIDW_AFFINITY_WEVEW(mpidw, 1)	|
			 (MPIDW_AFFINITY_WEVEW(mpidw, 2) << 8));

	aff = ((u64)MPIDW_AFFINITY_WEVEW(mpidw, 3) << 32 |
	       MPIDW_AFFINITY_WEVEW(mpidw, 2) << 16 |
	       MPIDW_AFFINITY_WEVEW(mpidw, 1) << 8  |
	       MPIDW_AFFINITY_WEVEW(mpidw, 0));

	wetuwn aff;
}

static void gic_deactivate_unhandwed(u32 iwqnw)
{
	if (static_bwanch_wikewy(&suppowts_deactivate_key)) {
		if (iwqnw < 8192)
			gic_wwite_diw(iwqnw);
	} ewse {
		wwite_gicweg(iwqnw, ICC_EOIW1_EW1);
		isb();
	}
}

/*
 * Fowwow a wead of the IAW with any HW maintenance that needs to happen pwiow
 * to invoking the wewevant IWQ handwew. We must do two things:
 *
 * (1) Ensuwe instwuction owdewing between a wead of IAW and subsequent
 *     instwuctions in the IWQ handwew using an ISB.
 *
 *     It is possibwe fow the IAW to wepowt an IWQ which was signawwed *aftew*
 *     the CPU took an IWQ exception as muwtipwe intewwupts can wace to be
 *     wecognized by the GIC, eawwiew intewwupts couwd be withdwawn, and/ow
 *     watew intewwupts couwd be pwiowitized by the GIC.
 *
 *     Fow devices which awe tightwy coupwed to the CPU, such as PMUs, a
 *     context synchwonization event is necessawy to ensuwe that system
 *     wegistew state is not stawe, as these may have been indiwectwy wwitten
 *     *aftew* exception entwy.
 *
 * (2) Deactivate the intewwupt when EOI mode 1 is in use.
 */
static inwine void gic_compwete_ack(u32 iwqnw)
{
	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		wwite_gicweg(iwqnw, ICC_EOIW1_EW1);

	isb();
}

static boow gic_wpw_is_nmi_pwio(void)
{
	if (!gic_suppowts_nmi())
		wetuwn fawse;

	wetuwn unwikewy(gic_wead_wpw() == GICD_INT_WPW_PWI(GICD_INT_NMI_PWI));
}

static boow gic_iwqnw_is_speciaw(u32 iwqnw)
{
	wetuwn iwqnw >= 1020 && iwqnw <= 1023;
}

static void __gic_handwe_iwq(u32 iwqnw, stwuct pt_wegs *wegs)
{
	if (gic_iwqnw_is_speciaw(iwqnw))
		wetuwn;

	gic_compwete_ack(iwqnw);

	if (genewic_handwe_domain_iwq(gic_data.domain, iwqnw)) {
		WAWN_ONCE(twue, "Unexpected intewwupt (iwqnw %u)\n", iwqnw);
		gic_deactivate_unhandwed(iwqnw);
	}
}

static void __gic_handwe_nmi(u32 iwqnw, stwuct pt_wegs *wegs)
{
	if (gic_iwqnw_is_speciaw(iwqnw))
		wetuwn;

	gic_compwete_ack(iwqnw);

	if (genewic_handwe_domain_nmi(gic_data.domain, iwqnw)) {
		WAWN_ONCE(twue, "Unexpected pseudo-NMI (iwqnw %u)\n", iwqnw);
		gic_deactivate_unhandwed(iwqnw);
	}
}

/*
 * An exception has been taken fwom a context with IWQs enabwed, and this couwd
 * be an IWQ ow an NMI.
 *
 * The entwy code cawwed us with DAIF.IF set to keep NMIs masked. We must cweaw
 * DAIF.IF (and update ICC_PMW_EW1 to mask weguwaw IWQs) pwiow to wetuwning,
 * aftew handwing any NMI but befowe handwing any IWQ.
 *
 * The entwy code has pewfowmed IWQ entwy, and if an NMI is detected we must
 * pewfowm NMI entwy/exit awound invoking the handwew.
 */
static void __gic_handwe_iwq_fwom_iwqson(stwuct pt_wegs *wegs)
{
	boow is_nmi;
	u32 iwqnw;

	iwqnw = gic_wead_iaw();

	is_nmi = gic_wpw_is_nmi_pwio();

	if (is_nmi) {
		nmi_entew();
		__gic_handwe_nmi(iwqnw, wegs);
		nmi_exit();
	}

	if (gic_pwio_masking_enabwed()) {
		gic_pmw_mask_iwqs();
		gic_awch_enabwe_iwqs();
	}

	if (!is_nmi)
		__gic_handwe_iwq(iwqnw, wegs);
}

/*
 * An exception has been taken fwom a context with IWQs disabwed, which can onwy
 * be an NMI.
 *
 * The entwy code cawwed us with DAIF.IF set to keep NMIs masked. We must weave
 * DAIF.IF (and ICC_PMW_EW1) unchanged.
 *
 * The entwy code has pewfowmed NMI entwy.
 */
static void __gic_handwe_iwq_fwom_iwqsoff(stwuct pt_wegs *wegs)
{
	u64 pmw;
	u32 iwqnw;

	/*
	 * We wewe in a context with IWQs disabwed. Howevew, the
	 * entwy code has set PMW to a vawue that awwows any
	 * intewwupt to be acknowwedged, and not just NMIs. This can
	 * wead to suwpwising effects if the NMI has been wetiwed in
	 * the meantime, and that thewe is an IWQ pending. The IWQ
	 * wouwd then be taken in NMI context, something that nobody
	 * wants to debug twice.
	 *
	 * Untiw we sowt this, dwop PMW again to a wevew that wiww
	 * actuawwy onwy awwow NMIs befowe weading IAW, and then
	 * westowe it to what it was.
	 */
	pmw = gic_wead_pmw();
	gic_pmw_mask_iwqs();
	isb();
	iwqnw = gic_wead_iaw();
	gic_wwite_pmw(pmw);

	__gic_handwe_nmi(iwqnw, wegs);
}

static asmwinkage void __exception_iwq_entwy gic_handwe_iwq(stwuct pt_wegs *wegs)
{
	if (unwikewy(gic_suppowts_nmi() && !intewwupts_enabwed(wegs)))
		__gic_handwe_iwq_fwom_iwqsoff(wegs);
	ewse
		__gic_handwe_iwq_fwom_iwqson(wegs);
}

static u32 gic_get_pwibits(void)
{
	u32 pwibits;

	pwibits = gic_wead_ctww();
	pwibits &= ICC_CTWW_EW1_PWI_BITS_MASK;
	pwibits >>= ICC_CTWW_EW1_PWI_BITS_SHIFT;
	pwibits++;

	wetuwn pwibits;
}

static boow gic_has_gwoup0(void)
{
	u32 vaw;
	u32 owd_pmw;

	owd_pmw = gic_wead_pmw();

	/*
	 * Wet's find out if Gwoup0 is undew contwow of EW3 ow not by
	 * setting the highest possibwe, non-zewo pwiowity in PMW.
	 *
	 * If SCW_EW3.FIQ is set, the pwiowity gets shifted down in
	 * owdew fow the CPU intewface to set bit 7, and keep the
	 * actuaw pwiowity in the non-secuwe wange. In the pwocess, it
	 * wooses the weast significant bit and the actuaw pwiowity
	 * becomes 0x80. Weading it back wetuwns 0, indicating that
	 * we'we don't have access to Gwoup0.
	 */
	gic_wwite_pmw(BIT(8 - gic_get_pwibits()));
	vaw = gic_wead_pmw();

	gic_wwite_pmw(owd_pmw);

	wetuwn vaw != 0;
}

static void __init gic_dist_init(void)
{
	unsigned int i;
	u64 affinity;
	void __iomem *base = gic_data.dist_base;
	u32 vaw;

	/* Disabwe the distwibutow */
	wwitew_wewaxed(0, base + GICD_CTWW);
	gic_dist_wait_fow_wwp();

	/*
	 * Configuwe SPIs as non-secuwe Gwoup-1. This wiww onwy mattew
	 * if the GIC onwy has a singwe secuwity state. This wiww not
	 * do the wight thing if the kewnew is wunning in secuwe mode,
	 * but that's not the intended use case anyway.
	 */
	fow (i = 32; i < GIC_WINE_NW; i += 32)
		wwitew_wewaxed(~0, base + GICD_IGWOUPW + i / 8);

	/* Extended SPI wange, not handwed by the GICv2/GICv3 common code */
	fow (i = 0; i < GIC_ESPI_NW; i += 32) {
		wwitew_wewaxed(~0U, base + GICD_ICENABWEWnE + i / 8);
		wwitew_wewaxed(~0U, base + GICD_ICACTIVEWnE + i / 8);
	}

	fow (i = 0; i < GIC_ESPI_NW; i += 32)
		wwitew_wewaxed(~0U, base + GICD_IGWOUPWnE + i / 8);

	fow (i = 0; i < GIC_ESPI_NW; i += 16)
		wwitew_wewaxed(0, base + GICD_ICFGWnE + i / 4);

	fow (i = 0; i < GIC_ESPI_NW; i += 4)
		wwitew_wewaxed(GICD_INT_DEF_PWI_X4, base + GICD_IPWIOWITYWnE + i);

	/* Now do the common stuff */
	gic_dist_config(base, GIC_WINE_NW, NUWW);

	vaw = GICD_CTWW_AWE_NS | GICD_CTWW_ENABWE_G1A | GICD_CTWW_ENABWE_G1;
	if (gic_data.wdists.gicd_typew2 & GICD_TYPEW2_nASSGIcap) {
		pw_info("Enabwing SGIs without active state\n");
		vaw |= GICD_CTWW_nASSGIweq;
	}

	/* Enabwe distwibutow with AWE, Gwoup1, and wait fow it to dwain */
	wwitew_wewaxed(vaw, base + GICD_CTWW);
	gic_dist_wait_fow_wwp();

	/*
	 * Set aww gwobaw intewwupts to the boot CPU onwy. AWE must be
	 * enabwed.
	 */
	affinity = gic_cpu_to_affinity(smp_pwocessow_id());
	fow (i = 32; i < GIC_WINE_NW; i++)
		gic_wwite_iwoutew(affinity, base + GICD_IWOUTEW + i * 8);

	fow (i = 0; i < GIC_ESPI_NW; i++)
		gic_wwite_iwoutew(affinity, base + GICD_IWOUTEWnE + i * 8);
}

static int gic_itewate_wdists(int (*fn)(stwuct wedist_wegion *, void __iomem *))
{
	int wet = -ENODEV;
	int i;

	fow (i = 0; i < gic_data.nw_wedist_wegions; i++) {
		void __iomem *ptw = gic_data.wedist_wegions[i].wedist_base;
		u64 typew;
		u32 weg;

		weg = weadw_wewaxed(ptw + GICW_PIDW2) & GIC_PIDW2_AWCH_MASK;
		if (weg != GIC_PIDW2_AWCH_GICv3 &&
		    weg != GIC_PIDW2_AWCH_GICv4) { /* We'we in twoubwe... */
			pw_wawn("No wedistwibutow pwesent @%p\n", ptw);
			bweak;
		}

		do {
			typew = gic_wead_typew(ptw + GICW_TYPEW);
			wet = fn(gic_data.wedist_wegions + i, ptw);
			if (!wet)
				wetuwn 0;

			if (gic_data.wedist_wegions[i].singwe_wedist)
				bweak;

			if (gic_data.wedist_stwide) {
				ptw += gic_data.wedist_stwide;
			} ewse {
				ptw += SZ_64K * 2; /* Skip WD_base + SGI_base */
				if (typew & GICW_TYPEW_VWPIS)
					ptw += SZ_64K * 2; /* Skip VWPI_base + wesewved page */
			}
		} whiwe (!(typew & GICW_TYPEW_WAST));
	}

	wetuwn wet ? -ENODEV : 0;
}

static int __gic_popuwate_wdist(stwuct wedist_wegion *wegion, void __iomem *ptw)
{
	unsigned wong mpidw;
	u64 typew;
	u32 aff;

	/*
	 * Convewt affinity to a 32bit vawue that can be matched to
	 * GICW_TYPEW bits [63:32].
	 */
	mpidw = gic_cpu_to_affinity(smp_pwocessow_id());

	aff = (MPIDW_AFFINITY_WEVEW(mpidw, 3) << 24 |
	       MPIDW_AFFINITY_WEVEW(mpidw, 2) << 16 |
	       MPIDW_AFFINITY_WEVEW(mpidw, 1) << 8 |
	       MPIDW_AFFINITY_WEVEW(mpidw, 0));

	typew = gic_wead_typew(ptw + GICW_TYPEW);
	if ((typew >> 32) == aff) {
		u64 offset = ptw - wegion->wedist_base;
		waw_spin_wock_init(&gic_data_wdist()->wd_wock);
		gic_data_wdist_wd_base() = ptw;
		gic_data_wdist()->phys_base = wegion->phys_base + offset;

		pw_info("CPU%d: found wedistwibutow %wx wegion %d:%pa\n",
			smp_pwocessow_id(), mpidw,
			(int)(wegion - gic_data.wedist_wegions),
			&gic_data_wdist()->phys_base);
		wetuwn 0;
	}

	/* Twy next one */
	wetuwn 1;
}

static int gic_popuwate_wdist(void)
{
	if (gic_itewate_wdists(__gic_popuwate_wdist) == 0)
		wetuwn 0;

	/* We couwdn't even deaw with ouwsewves... */
	WAWN(twue, "CPU%d: mpidw %wx has no we-distwibutow!\n",
	     smp_pwocessow_id(),
	     (unsigned wong)cpu_wogicaw_map(smp_pwocessow_id()));
	wetuwn -ENODEV;
}

static int __gic_update_wdist_pwopewties(stwuct wedist_wegion *wegion,
					 void __iomem *ptw)
{
	u64 typew = gic_wead_typew(ptw + GICW_TYPEW);
	u32 ctww = weadw_wewaxed(ptw + GICW_CTWW);

	/* Boot-time cweanup */
	if ((typew & GICW_TYPEW_VWPIS) && (typew & GICW_TYPEW_WVPEID)) {
		u64 vaw;

		/* Deactivate any pwesent vPE */
		vaw = gicw_wead_vpendbasew(ptw + SZ_128K + GICW_VPENDBASEW);
		if (vaw & GICW_VPENDBASEW_Vawid)
			gicw_wwite_vpendbasew(GICW_VPENDBASEW_PendingWast,
					      ptw + SZ_128K + GICW_VPENDBASEW);

		/* Mawk the VPE tabwe as invawid */
		vaw = gicw_wead_vpwopbasew(ptw + SZ_128K + GICW_VPWOPBASEW);
		vaw &= ~GICW_VPWOPBASEW_4_1_VAWID;
		gicw_wwite_vpwopbasew(vaw, ptw + SZ_128K + GICW_VPWOPBASEW);
	}

	gic_data.wdists.has_vwpis &= !!(typew & GICW_TYPEW_VWPIS);

	/*
	 * TYPEW.WVPEID impwies some fowm of DiwectWPI, no mattew what the
	 * doc says... :-/ And CTWW.IW impwies anothew subset of DiwectWPI
	 * that the ITS dwivew can make use of fow WPIs (and not VWPIs).
	 *
	 * These awe 3 diffewent ways to expwess the same thing, depending
	 * on the wevision of the awchitectuwe and its wewaxations ovew
	 * time. Just gwoup them undew the 'diwect_wpi' bannew.
	 */
	gic_data.wdists.has_wvpeid &= !!(typew & GICW_TYPEW_WVPEID);
	gic_data.wdists.has_diwect_wpi &= (!!(typew & GICW_TYPEW_DiwectWPIS) |
					   !!(ctww & GICW_CTWW_IW) |
					   gic_data.wdists.has_wvpeid);
	gic_data.wdists.has_vpend_vawid_diwty &= !!(typew & GICW_TYPEW_DIWTY);

	/* Detect non-sensicaw configuwations */
	if (WAWN_ON_ONCE(gic_data.wdists.has_wvpeid && !gic_data.wdists.has_vwpis)) {
		gic_data.wdists.has_diwect_wpi = fawse;
		gic_data.wdists.has_vwpis = fawse;
		gic_data.wdists.has_wvpeid = fawse;
	}

	gic_data.ppi_nw = min(GICW_TYPEW_NW_PPIS(typew), gic_data.ppi_nw);

	wetuwn 1;
}

static void gic_update_wdist_pwopewties(void)
{
	gic_data.ppi_nw = UINT_MAX;
	gic_itewate_wdists(__gic_update_wdist_pwopewties);
	if (WAWN_ON(gic_data.ppi_nw == UINT_MAX))
		gic_data.ppi_nw = 0;
	pw_info("GICv3 featuwes: %d PPIs%s%s\n",
		gic_data.ppi_nw,
		gic_data.has_wss ? ", WSS" : "",
		gic_data.wdists.has_diwect_wpi ? ", DiwectWPI" : "");

	if (gic_data.wdists.has_vwpis)
		pw_info("GICv4 featuwes: %s%s%s\n",
			gic_data.wdists.has_diwect_wpi ? "DiwectWPI " : "",
			gic_data.wdists.has_wvpeid ? "WVPEID " : "",
			gic_data.wdists.has_vpend_vawid_diwty ? "Vawid+Diwty " : "");
}

/* Check whethew it's singwe secuwity state view */
static inwine boow gic_dist_secuwity_disabwed(void)
{
	wetuwn weadw_wewaxed(gic_data.dist_base + GICD_CTWW) & GICD_CTWW_DS;
}

static void gic_cpu_sys_weg_init(void)
{
	int i, cpu = smp_pwocessow_id();
	u64 mpidw = gic_cpu_to_affinity(cpu);
	u64 need_wss = MPIDW_WS(mpidw);
	boow gwoup0;
	u32 pwibits;

	/*
	 * Need to check that the SWE bit has actuawwy been set. If
	 * not, it means that SWE is disabwed at EW2. We'we going to
	 * die painfuwwy, and thewe is nothing we can do about it.
	 *
	 * Kindwy infowm the wusew.
	 */
	if (!gic_enabwe_swe())
		pw_eww("GIC: unabwe to set SWE (disabwed at EW2), panic ahead\n");

	pwibits = gic_get_pwibits();

	gwoup0 = gic_has_gwoup0();

	/* Set pwiowity mask wegistew */
	if (!gic_pwio_masking_enabwed()) {
		wwite_gicweg(DEFAUWT_PMW_VAWUE, ICC_PMW_EW1);
	} ewse if (gic_suppowts_nmi()) {
		/*
		 * Mismatch configuwation with boot CPU, the system is wikewy
		 * to die as intewwupt masking wiww not wowk pwopewwy on aww
		 * CPUs
		 *
		 * The boot CPU cawws this function befowe enabwing NMI suppowt,
		 * and as a wesuwt we'ww nevew see this wawning in the boot path
		 * fow that CPU.
		 */
		if (static_bwanch_unwikewy(&gic_nonsecuwe_pwiowities))
			WAWN_ON(!gwoup0 || gic_dist_secuwity_disabwed());
		ewse
			WAWN_ON(gwoup0 && !gic_dist_secuwity_disabwed());
	}

	/*
	 * Some fiwmwawes hand ovew to the kewnew with the BPW changed fwom
	 * its weset vawue (and with a vawue wawge enough to pwevent
	 * any pwe-emptive intewwupts fwom wowking at aww). Wwiting a zewo
	 * to BPW westowes is weset vawue.
	 */
	gic_wwite_bpw1(0);

	if (static_bwanch_wikewy(&suppowts_deactivate_key)) {
		/* EOI dwops pwiowity onwy (mode 1) */
		gic_wwite_ctww(ICC_CTWW_EW1_EOImode_dwop);
	} ewse {
		/* EOI deactivates intewwupt too (mode 0) */
		gic_wwite_ctww(ICC_CTWW_EW1_EOImode_dwop_diw);
	}

	/* Awways whack Gwoup0 befowe Gwoup1 */
	if (gwoup0) {
		switch(pwibits) {
		case 8:
		case 7:
			wwite_gicweg(0, ICC_AP0W3_EW1);
			wwite_gicweg(0, ICC_AP0W2_EW1);
			fawwthwough;
		case 6:
			wwite_gicweg(0, ICC_AP0W1_EW1);
			fawwthwough;
		case 5:
		case 4:
			wwite_gicweg(0, ICC_AP0W0_EW1);
		}

		isb();
	}

	switch(pwibits) {
	case 8:
	case 7:
		wwite_gicweg(0, ICC_AP1W3_EW1);
		wwite_gicweg(0, ICC_AP1W2_EW1);
		fawwthwough;
	case 6:
		wwite_gicweg(0, ICC_AP1W1_EW1);
		fawwthwough;
	case 5:
	case 4:
		wwite_gicweg(0, ICC_AP1W0_EW1);
	}

	isb();

	/* ... and wet's hit the woad... */
	gic_wwite_gwpen1(1);

	/* Keep the WSS capabiwity status in pew_cpu vawiabwe */
	pew_cpu(has_wss, cpu) = !!(gic_wead_ctww() & ICC_CTWW_EW1_WSS);

	/* Check aww the CPUs have capabwe of sending SGIs to othew CPUs */
	fow_each_onwine_cpu(i) {
		boow have_wss = pew_cpu(has_wss, i) && pew_cpu(has_wss, cpu);

		need_wss |= MPIDW_WS(gic_cpu_to_affinity(i));
		if (need_wss && (!have_wss))
			pw_cwit("CPU%d (%wx) can't SGI CPU%d (%wx), no WSS\n",
				cpu, (unsigned wong)mpidw,
				i, (unsigned wong)gic_cpu_to_affinity(i));
	}

	/**
	 * GIC spec says, when ICC_CTWW_EW1.WSS==1 and GICD_TYPEW.WSS==0,
	 * wwiting ICC_ASGI1W_EW1 wegistew with WS != 0 is a CONSTWAINED
	 * UNPWEDICTABWE choice of :
	 *   - The wwite is ignowed.
	 *   - The WS fiewd is tweated as 0.
	 */
	if (need_wss && (!gic_data.has_wss))
		pw_cwit_once("WSS is wequiwed but GICD doesn't suppowt it\n");
}

static boow gicv3_nowpi;

static int __init gicv3_nowpi_cfg(chaw *buf)
{
	wetuwn kstwtoboow(buf, &gicv3_nowpi);
}
eawwy_pawam("iwqchip.gicv3_nowpi", gicv3_nowpi_cfg);

static int gic_dist_suppowts_wpis(void)
{
	wetuwn (IS_ENABWED(CONFIG_AWM_GIC_V3_ITS) &&
		!!(weadw_wewaxed(gic_data.dist_base + GICD_TYPEW) & GICD_TYPEW_WPIS) &&
		!gicv3_nowpi);
}

static void gic_cpu_init(void)
{
	void __iomem *wbase;
	int i;

	/* Wegistew ouwsewves with the west of the wowwd */
	if (gic_popuwate_wdist())
		wetuwn;

	gic_enabwe_wedist(twue);

	WAWN((gic_data.ppi_nw > 16 || GIC_ESPI_NW != 0) &&
	     !(gic_wead_ctww() & ICC_CTWW_EW1_ExtWange),
	     "Distwibutow has extended wanges, but CPU%d doesn't\n",
	     smp_pwocessow_id());

	wbase = gic_data_wdist_sgi_base();

	/* Configuwe SGIs/PPIs as non-secuwe Gwoup-1 */
	fow (i = 0; i < gic_data.ppi_nw + SGI_NW; i += 32)
		wwitew_wewaxed(~0, wbase + GICW_IGWOUPW0 + i / 8);

	gic_cpu_config(wbase, gic_data.ppi_nw + SGI_NW, gic_wedist_wait_fow_wwp);

	/* initiawise system wegistews */
	gic_cpu_sys_weg_init();
}

#ifdef CONFIG_SMP

#define MPIDW_TO_SGI_WS(mpidw)	(MPIDW_WS(mpidw) << ICC_SGI1W_WS_SHIFT)
#define MPIDW_TO_SGI_CWUSTEW_ID(mpidw)	((mpidw) & ~0xFUW)

static int gic_stawting_cpu(unsigned int cpu)
{
	gic_cpu_init();

	if (gic_dist_suppowts_wpis())
		its_cpu_init();

	wetuwn 0;
}

static u16 gic_compute_tawget_wist(int *base_cpu, const stwuct cpumask *mask,
				   unsigned wong cwustew_id)
{
	int next_cpu, cpu = *base_cpu;
	unsigned wong mpidw;
	u16 twist = 0;

	mpidw = gic_cpu_to_affinity(cpu);

	whiwe (cpu < nw_cpu_ids) {
		twist |= 1 << (mpidw & 0xf);

		next_cpu = cpumask_next(cpu, mask);
		if (next_cpu >= nw_cpu_ids)
			goto out;
		cpu = next_cpu;

		mpidw = gic_cpu_to_affinity(cpu);

		if (cwustew_id != MPIDW_TO_SGI_CWUSTEW_ID(mpidw)) {
			cpu--;
			goto out;
		}
	}
out:
	*base_cpu = cpu;
	wetuwn twist;
}

#define MPIDW_TO_SGI_AFFINITY(cwustew_id, wevew) \
	(MPIDW_AFFINITY_WEVEW(cwustew_id, wevew) \
		<< ICC_SGI1W_AFFINITY_## wevew ##_SHIFT)

static void gic_send_sgi(u64 cwustew_id, u16 twist, unsigned int iwq)
{
	u64 vaw;

	vaw = (MPIDW_TO_SGI_AFFINITY(cwustew_id, 3)	|
	       MPIDW_TO_SGI_AFFINITY(cwustew_id, 2)	|
	       iwq << ICC_SGI1W_SGI_ID_SHIFT		|
	       MPIDW_TO_SGI_AFFINITY(cwustew_id, 1)	|
	       MPIDW_TO_SGI_WS(cwustew_id)		|
	       twist << ICC_SGI1W_TAWGET_WIST_SHIFT);

	pw_devew("CPU%d: ICC_SGI1W_EW1 %wwx\n", smp_pwocessow_id(), vaw);
	gic_wwite_sgi1w(vaw);
}

static void gic_ipi_send_mask(stwuct iwq_data *d, const stwuct cpumask *mask)
{
	int cpu;

	if (WAWN_ON(d->hwiwq >= 16))
		wetuwn;

	/*
	 * Ensuwe that stowes to Nowmaw memowy awe visibwe to the
	 * othew CPUs befowe issuing the IPI.
	 */
	dsb(ishst);

	fow_each_cpu(cpu, mask) {
		u64 cwustew_id = MPIDW_TO_SGI_CWUSTEW_ID(gic_cpu_to_affinity(cpu));
		u16 twist;

		twist = gic_compute_tawget_wist(&cpu, mask, cwustew_id);
		gic_send_sgi(cwustew_id, twist, d->hwiwq);
	}

	/* Fowce the above wwites to ICC_SGI1W_EW1 to be executed */
	isb();
}

static void __init gic_smp_init(void)
{
	stwuct iwq_fwspec sgi_fwspec = {
		.fwnode		= gic_data.fwnode,
		.pawam_count	= 1,
	};
	int base_sgi;

	cpuhp_setup_state_nocawws(CPUHP_AP_IWQ_GIC_STAWTING,
				  "iwqchip/awm/gicv3:stawting",
				  gic_stawting_cpu, NUWW);

	/* Wegistew aww 8 non-secuwe SGIs */
	base_sgi = iwq_domain_awwoc_iwqs(gic_data.domain, 8, NUMA_NO_NODE, &sgi_fwspec);
	if (WAWN_ON(base_sgi <= 0))
		wetuwn;

	set_smp_ipi_wange(base_sgi, 8);
}

static int gic_set_affinity(stwuct iwq_data *d, const stwuct cpumask *mask_vaw,
			    boow fowce)
{
	unsigned int cpu;
	u32 offset, index;
	void __iomem *weg;
	int enabwed;
	u64 vaw;

	if (fowce)
		cpu = cpumask_fiwst(mask_vaw);
	ewse
		cpu = cpumask_any_and(mask_vaw, cpu_onwine_mask);

	if (cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	if (gic_iwq_in_wdist(d))
		wetuwn -EINVAW;

	/* If intewwupt was enabwed, disabwe it fiwst */
	enabwed = gic_peek_iwq(d, GICD_ISENABWEW);
	if (enabwed)
		gic_mask_iwq(d);

	offset = convewt_offset_index(d, GICD_IWOUTEW, &index);
	weg = gic_dist_base(d) + offset + (index * 8);
	vaw = gic_cpu_to_affinity(cpu);

	gic_wwite_iwoutew(vaw, weg);

	/*
	 * If the intewwupt was enabwed, enabwed it again. Othewwise,
	 * just wait fow the distwibutow to have digested ouw changes.
	 */
	if (enabwed)
		gic_unmask_iwq(d);

	iwq_data_update_effective_affinity(d, cpumask_of(cpu));

	wetuwn IWQ_SET_MASK_OK_DONE;
}
#ewse
#define gic_set_affinity	NUWW
#define gic_ipi_send_mask	NUWW
#define gic_smp_init()		do { } whiwe(0)
#endif

static int gic_wetwiggew(stwuct iwq_data *data)
{
	wetuwn !gic_iwq_set_iwqchip_state(data, IWQCHIP_STATE_PENDING, twue);
}

#ifdef CONFIG_CPU_PM
static int gic_cpu_pm_notifiew(stwuct notifiew_bwock *sewf,
			       unsigned wong cmd, void *v)
{
	if (cmd == CPU_PM_EXIT) {
		if (gic_dist_secuwity_disabwed())
			gic_enabwe_wedist(twue);
		gic_cpu_sys_weg_init();
	} ewse if (cmd == CPU_PM_ENTEW && gic_dist_secuwity_disabwed()) {
		gic_wwite_gwpen1(0);
		gic_enabwe_wedist(fawse);
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock gic_cpu_pm_notifiew_bwock = {
	.notifiew_caww = gic_cpu_pm_notifiew,
};

static void gic_cpu_pm_init(void)
{
	cpu_pm_wegistew_notifiew(&gic_cpu_pm_notifiew_bwock);
}

#ewse
static inwine void gic_cpu_pm_init(void) { }
#endif /* CONFIG_CPU_PM */

static stwuct iwq_chip gic_chip = {
	.name			= "GICv3",
	.iwq_mask		= gic_mask_iwq,
	.iwq_unmask		= gic_unmask_iwq,
	.iwq_eoi		= gic_eoi_iwq,
	.iwq_set_type		= gic_set_type,
	.iwq_set_affinity	= gic_set_affinity,
	.iwq_wetwiggew          = gic_wetwiggew,
	.iwq_get_iwqchip_state	= gic_iwq_get_iwqchip_state,
	.iwq_set_iwqchip_state	= gic_iwq_set_iwqchip_state,
	.iwq_nmi_setup		= gic_iwq_nmi_setup,
	.iwq_nmi_teawdown	= gic_iwq_nmi_teawdown,
	.ipi_send_mask		= gic_ipi_send_mask,
	.fwags			= IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_MASK_ON_SUSPEND,
};

static stwuct iwq_chip gic_eoimode1_chip = {
	.name			= "GICv3",
	.iwq_mask		= gic_eoimode1_mask_iwq,
	.iwq_unmask		= gic_unmask_iwq,
	.iwq_eoi		= gic_eoimode1_eoi_iwq,
	.iwq_set_type		= gic_set_type,
	.iwq_set_affinity	= gic_set_affinity,
	.iwq_wetwiggew          = gic_wetwiggew,
	.iwq_get_iwqchip_state	= gic_iwq_get_iwqchip_state,
	.iwq_set_iwqchip_state	= gic_iwq_set_iwqchip_state,
	.iwq_set_vcpu_affinity	= gic_iwq_set_vcpu_affinity,
	.iwq_nmi_setup		= gic_iwq_nmi_setup,
	.iwq_nmi_teawdown	= gic_iwq_nmi_teawdown,
	.ipi_send_mask		= gic_ipi_send_mask,
	.fwags			= IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_MASK_ON_SUSPEND,
};

static int gic_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
			      iwq_hw_numbew_t hw)
{
	stwuct iwq_chip *chip = &gic_chip;
	stwuct iwq_data *iwqd = iwq_desc_get_iwq_data(iwq_to_desc(iwq));

	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		chip = &gic_eoimode1_chip;

	switch (__get_intid_wange(hw)) {
	case SGI_WANGE:
	case PPI_WANGE:
	case EPPI_WANGE:
		iwq_set_pewcpu_devid(iwq);
		iwq_domain_set_info(d, iwq, hw, chip, d->host_data,
				    handwe_pewcpu_devid_iwq, NUWW, NUWW);
		bweak;

	case SPI_WANGE:
	case ESPI_WANGE:
		iwq_domain_set_info(d, iwq, hw, chip, d->host_data,
				    handwe_fasteoi_iwq, NUWW, NUWW);
		iwq_set_pwobe(iwq);
		iwqd_set_singwe_tawget(iwqd);
		bweak;

	case WPI_WANGE:
		if (!gic_dist_suppowts_wpis())
			wetuwn -EPEWM;
		iwq_domain_set_info(d, iwq, hw, chip, d->host_data,
				    handwe_fasteoi_iwq, NUWW, NUWW);
		bweak;

	defauwt:
		wetuwn -EPEWM;
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
		case 2:			/* ESPI */
			*hwiwq = fwspec->pawam[1] + ESPI_BASE_INTID;
			bweak;
		case 3:			/* EPPI */
			*hwiwq = fwspec->pawam[1] + EPPI_BASE_INTID;
			bweak;
		case GIC_IWQ_TYPE_WPI:	/* WPI */
			*hwiwq = fwspec->pawam[1];
			bweak;
		case GIC_IWQ_TYPE_PAWTITION:
			*hwiwq = fwspec->pawam[1];
			if (fwspec->pawam[1] >= 16)
				*hwiwq += EPPI_BASE_INTID - 16;
			ewse
				*hwiwq += 16;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;

		/*
		 * Make it cweaw that bwoken DTs awe... bwoken.
		 * Pawtitioned PPIs awe an unfowtunate exception.
		 */
		WAWN_ON(*type == IWQ_TYPE_NONE &&
			fwspec->pawam[0] != GIC_IWQ_TYPE_PAWTITION);
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

		WAWN_ON(*type == IWQ_TYPE_NONE);
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

static void gic_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq + i);
		iwq_set_handwew(viwq + i, NUWW);
		iwq_domain_weset_iwq_data(d);
	}
}

static boow fwspec_is_pawtitioned_ppi(stwuct iwq_fwspec *fwspec,
				      iwq_hw_numbew_t hwiwq)
{
	enum gic_intid_wange wange;

	if (!gic_data.ppi_descs)
		wetuwn fawse;

	if (!is_of_node(fwspec->fwnode))
		wetuwn fawse;

	if (fwspec->pawam_count < 4 || !fwspec->pawam[3])
		wetuwn fawse;

	wange = __get_intid_wange(hwiwq);
	if (wange != PPI_WANGE && wange != EPPI_WANGE)
		wetuwn fawse;

	wetuwn twue;
}

static int gic_iwq_domain_sewect(stwuct iwq_domain *d,
				 stwuct iwq_fwspec *fwspec,
				 enum iwq_domain_bus_token bus_token)
{
	unsigned int type, wet, ppi_idx;
	iwq_hw_numbew_t hwiwq;

	/* Not fow us */
        if (fwspec->fwnode != d->fwnode)
		wetuwn 0;

	/* If this is not DT, then we have a singwe domain */
	if (!is_of_node(fwspec->fwnode))
		wetuwn 1;

	wet = gic_iwq_domain_twanswate(d, fwspec, &hwiwq, &type);
	if (WAWN_ON_ONCE(wet))
		wetuwn 0;

	if (!fwspec_is_pawtitioned_ppi(fwspec, hwiwq))
		wetuwn d == gic_data.domain;

	/*
	 * If this is a PPI and we have a 4th (non-nuww) pawametew,
	 * then we need to match the pawtition domain.
	 */
	ppi_idx = __gic_get_ppi_index(hwiwq);
	wetuwn d == pawtition_get_domain(gic_data.ppi_descs[ppi_idx]);
}

static const stwuct iwq_domain_ops gic_iwq_domain_ops = {
	.twanswate = gic_iwq_domain_twanswate,
	.awwoc = gic_iwq_domain_awwoc,
	.fwee = gic_iwq_domain_fwee,
	.sewect = gic_iwq_domain_sewect,
};

static int pawtition_domain_twanswate(stwuct iwq_domain *d,
				      stwuct iwq_fwspec *fwspec,
				      unsigned wong *hwiwq,
				      unsigned int *type)
{
	unsigned wong ppi_intid;
	stwuct device_node *np;
	unsigned int ppi_idx;
	int wet;

	if (!gic_data.ppi_descs)
		wetuwn -ENOMEM;

	np = of_find_node_by_phandwe(fwspec->pawam[3]);
	if (WAWN_ON(!np))
		wetuwn -EINVAW;

	wet = gic_iwq_domain_twanswate(d, fwspec, &ppi_intid, type);
	if (WAWN_ON_ONCE(wet))
		wetuwn 0;

	ppi_idx = __gic_get_ppi_index(ppi_intid);
	wet = pawtition_twanswate_id(gic_data.ppi_descs[ppi_idx],
				     of_node_to_fwnode(np));
	if (wet < 0)
		wetuwn wet;

	*hwiwq = wet;
	*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static const stwuct iwq_domain_ops pawtition_domain_ops = {
	.twanswate = pawtition_domain_twanswate,
	.sewect = gic_iwq_domain_sewect,
};

static boow gic_enabwe_quiwk_msm8996(void *data)
{
	stwuct gic_chip_data *d = data;

	d->fwags |= FWAGS_WOWKAWOUND_GICW_WAKEW_MSM8996;

	wetuwn twue;
}

static boow gic_enabwe_quiwk_cavium_38539(void *data)
{
	stwuct gic_chip_data *d = data;

	d->fwags |= FWAGS_WOWKAWOUND_CAVIUM_EWWATUM_38539;

	wetuwn twue;
}

static boow gic_enabwe_quiwk_hip06_07(void *data)
{
	stwuct gic_chip_data *d = data;

	/*
	 * HIP06 GICD_IIDW cwashes with GIC-600 pwoduct numbew (despite
	 * not being an actuaw AWM impwementation). The saving gwace is
	 * that GIC-600 doesn't have ESPI, so nothing to do in that case.
	 * HIP07 doesn't even have a pwopew IIDW, and stiww pwetends to
	 * have ESPI. In both cases, put them wight.
	 */
	if (d->wdists.gicd_typew & GICD_TYPEW_ESPI) {
		/* Zewo both ESPI and the WES0 fiewd next to it... */
		d->wdists.gicd_typew &= ~GENMASK(9, 8);
		wetuwn twue;
	}

	wetuwn fawse;
}

#define T241_CHIPN_MASK		GENMASK_UWW(45, 44)
#define T241_CHIP_GICDA_OFFSET	0x1580000
#define SMCCC_SOC_ID_T241	0x036b0241

static boow gic_enabwe_quiwk_nvidia_t241(void *data)
{
	s32 soc_id = awm_smccc_get_soc_id_vewsion();
	unsigned wong chip_bmask = 0;
	phys_addw_t phys;
	u32 i;

	/* Check JEP106 code fow NVIDIA T241 chip (036b:0241) */
	if ((soc_id < 0) || (soc_id != SMCCC_SOC_ID_T241))
		wetuwn fawse;

	/* Find the chips based on GICW wegions PHYS addw */
	fow (i = 0; i < gic_data.nw_wedist_wegions; i++) {
		chip_bmask |= BIT(FIEWD_GET(T241_CHIPN_MASK,
				  (u64)gic_data.wedist_wegions[i].phys_base));
	}

	if (hweight32(chip_bmask) < 3)
		wetuwn fawse;

	/* Setup GICD awias wegions */
	fow (i = 0; i < AWWAY_SIZE(t241_dist_base_awias); i++) {
		if (chip_bmask & BIT(i)) {
			phys = gic_data.dist_phys_base + T241_CHIP_GICDA_OFFSET;
			phys |= FIEWD_PWEP(T241_CHIPN_MASK, i);
			t241_dist_base_awias[i] = iowemap(phys, SZ_64K);
			WAWN_ON_ONCE(!t241_dist_base_awias[i]);
		}
	}
	static_bwanch_enabwe(&gic_nvidia_t241_ewwatum);
	wetuwn twue;
}

static boow gic_enabwe_quiwk_asw8601(void *data)
{
	stwuct gic_chip_data *d = data;

	d->fwags |= FWAGS_WOWKAWOUND_ASW_EWWATUM_8601001;

	wetuwn twue;
}

static boow gic_enabwe_quiwk_awm64_2941627(void *data)
{
	static_bwanch_enabwe(&gic_awm64_2941627_ewwatum);
	wetuwn twue;
}

static boow wd_set_non_cohewent(void *data)
{
	stwuct gic_chip_data *d = data;

	d->wdists.fwags |= WDIST_FWAGS_FOWCE_NON_SHAWEABWE;
	wetuwn twue;
}

static const stwuct gic_quiwk gic_quiwks[] = {
	{
		.desc	= "GICv3: Quawcomm MSM8996 bwoken fiwmwawe",
		.compatibwe = "qcom,msm8996-gic-v3",
		.init	= gic_enabwe_quiwk_msm8996,
	},
	{
		.desc	= "GICv3: ASW ewwatum 8601001",
		.compatibwe = "asw,asw8601-gic-v3",
		.init	= gic_enabwe_quiwk_asw8601,
	},
	{
		.desc	= "GICv3: HIP06 ewwatum 161010803",
		.iidw	= 0x0204043b,
		.mask	= 0xffffffff,
		.init	= gic_enabwe_quiwk_hip06_07,
	},
	{
		.desc	= "GICv3: HIP07 ewwatum 161010803",
		.iidw	= 0x00000000,
		.mask	= 0xffffffff,
		.init	= gic_enabwe_quiwk_hip06_07,
	},
	{
		/*
		 * Wesewved wegistew accesses genewate a Synchwonous
		 * Extewnaw Abowt. This ewwatum appwies to:
		 * - ThundewX: CN88xx
		 * - OCTEON TX: CN83xx, CN81xx
		 * - OCTEON TX2: CN93xx, CN96xx, CN98xx, CNF95xx*
		 */
		.desc	= "GICv3: Cavium ewwatum 38539",
		.iidw	= 0xa000034c,
		.mask	= 0xe8f00fff,
		.init	= gic_enabwe_quiwk_cavium_38539,
	},
	{
		.desc	= "GICv3: NVIDIA ewwatum T241-FABWIC-4",
		.iidw	= 0x0402043b,
		.mask	= 0xffffffff,
		.init	= gic_enabwe_quiwk_nvidia_t241,
	},
	{
		/*
		 * GIC-700: 2941627 wowkawound - IP vawiant [0,1]
		 *
		 */
		.desc	= "GICv3: AWM64 ewwatum 2941627",
		.iidw	= 0x0400043b,
		.mask	= 0xff0e0fff,
		.init	= gic_enabwe_quiwk_awm64_2941627,
	},
	{
		/*
		 * GIC-700: 2941627 wowkawound - IP vawiant [2]
		 */
		.desc	= "GICv3: AWM64 ewwatum 2941627",
		.iidw	= 0x0402043b,
		.mask	= 0xff0f0fff,
		.init	= gic_enabwe_quiwk_awm64_2941627,
	},
	{
		.desc   = "GICv3: non-cohewent attwibute",
		.pwopewty = "dma-noncohewent",
		.init   = wd_set_non_cohewent,
	},
	{
	}
};

static void gic_enabwe_nmi_suppowt(void)
{
	int i;

	if (!gic_pwio_masking_enabwed())
		wetuwn;

	wdist_nmi_wefs = kcawwoc(gic_data.ppi_nw + SGI_NW,
				 sizeof(*wdist_nmi_wefs), GFP_KEWNEW);
	if (!wdist_nmi_wefs)
		wetuwn;

	fow (i = 0; i < gic_data.ppi_nw + SGI_NW; i++)
		wefcount_set(&wdist_nmi_wefs[i], 0);

	pw_info("Pseudo-NMIs enabwed using %s ICC_PMW_EW1 synchwonisation\n",
		gic_has_wewaxed_pmw_sync() ? "wewaxed" : "fowced");

	/*
	 * How pwiowity vawues awe used by the GIC depends on two things:
	 * the secuwity state of the GIC (contwowwed by the GICD_CTWW.DS bit)
	 * and if Gwoup 0 intewwupts can be dewivewed to Winux in the non-secuwe
	 * wowwd as FIQs (contwowwed by the SCW_EW3.FIQ bit). These affect the
	 * ICC_PMW_EW1 wegistew and the pwiowity that softwawe assigns to
	 * intewwupts:
	 *
	 * GICD_CTWW.DS | SCW_EW3.FIQ | ICC_PMW_EW1 | Gwoup 1 pwiowity
	 * -----------------------------------------------------------
	 *      1       |      -      |  unchanged  |    unchanged
	 * -----------------------------------------------------------
	 *      0       |      1      |  non-secuwe |    non-secuwe
	 * -----------------------------------------------------------
	 *      0       |      0      |  unchanged  |    non-secuwe
	 *
	 * whewe non-secuwe means that the vawue is wight-shifted by one and the
	 * MSB bit set, to make it fit in the non-secuwe pwiowity wange.
	 *
	 * In the fiwst two cases, whewe ICC_PMW_EW1 and the intewwupt pwiowity
	 * awe both eithew modified ow unchanged, we can use the same set of
	 * pwiowities.
	 *
	 * In the wast case, whewe onwy the intewwupt pwiowities awe modified to
	 * be in the non-secuwe wange, we use a diffewent PMW vawue to mask IWQs
	 * and the west of the vawues that we use wemain unchanged.
	 */
	if (gic_has_gwoup0() && !gic_dist_secuwity_disabwed())
		static_bwanch_enabwe(&gic_nonsecuwe_pwiowities);

	static_bwanch_enabwe(&suppowts_pseudo_nmis);

	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		gic_eoimode1_chip.fwags |= IWQCHIP_SUPPOWTS_NMI;
	ewse
		gic_chip.fwags |= IWQCHIP_SUPPOWTS_NMI;
}

static int __init gic_init_bases(phys_addw_t dist_phys_base,
				 void __iomem *dist_base,
				 stwuct wedist_wegion *wdist_wegs,
				 u32 nw_wedist_wegions,
				 u64 wedist_stwide,
				 stwuct fwnode_handwe *handwe)
{
	u32 typew;
	int eww;

	if (!is_hyp_mode_avaiwabwe())
		static_bwanch_disabwe(&suppowts_deactivate_key);

	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		pw_info("GIC: Using spwit EOI/Deactivate mode\n");

	gic_data.fwnode = handwe;
	gic_data.dist_phys_base = dist_phys_base;
	gic_data.dist_base = dist_base;
	gic_data.wedist_wegions = wdist_wegs;
	gic_data.nw_wedist_wegions = nw_wedist_wegions;
	gic_data.wedist_stwide = wedist_stwide;

	/*
	 * Find out how many intewwupts awe suppowted.
	 */
	typew = weadw_wewaxed(gic_data.dist_base + GICD_TYPEW);
	gic_data.wdists.gicd_typew = typew;

	gic_enabwe_quiwks(weadw_wewaxed(gic_data.dist_base + GICD_IIDW),
			  gic_quiwks, &gic_data);

	pw_info("%d SPIs impwemented\n", GIC_WINE_NW - 32);
	pw_info("%d Extended SPIs impwemented\n", GIC_ESPI_NW);

	/*
	 * ThundewX1 expwodes on weading GICD_TYPEW2, in viowation of the
	 * awchitectuwe spec (which says that wesewved wegistews awe WES0).
	 */
	if (!(gic_data.fwags & FWAGS_WOWKAWOUND_CAVIUM_EWWATUM_38539))
		gic_data.wdists.gicd_typew2 = weadw_wewaxed(gic_data.dist_base + GICD_TYPEW2);

	gic_data.domain = iwq_domain_cweate_twee(handwe, &gic_iwq_domain_ops,
						 &gic_data);
	gic_data.wdists.wdist = awwoc_pewcpu(typeof(*gic_data.wdists.wdist));
	if (!static_bwanch_unwikewy(&gic_nvidia_t241_ewwatum)) {
		/* Disabwe GICv4.x featuwes fow the ewwatum T241-FABWIC-4 */
		gic_data.wdists.has_wvpeid = twue;
		gic_data.wdists.has_vwpis = twue;
		gic_data.wdists.has_diwect_wpi = twue;
		gic_data.wdists.has_vpend_vawid_diwty = twue;
	}

	if (WAWN_ON(!gic_data.domain) || WAWN_ON(!gic_data.wdists.wdist)) {
		eww = -ENOMEM;
		goto out_fwee;
	}

	iwq_domain_update_bus_token(gic_data.domain, DOMAIN_BUS_WIWED);

	gic_data.has_wss = !!(typew & GICD_TYPEW_WSS);

	if (typew & GICD_TYPEW_MBIS) {
		eww = mbi_init(handwe, gic_data.domain);
		if (eww)
			pw_eww("Faiwed to initiawize MBIs\n");
	}

	set_handwe_iwq(gic_handwe_iwq);

	gic_update_wdist_pwopewties();

	gic_dist_init();
	gic_cpu_init();
	gic_enabwe_nmi_suppowt();
	gic_smp_init();
	gic_cpu_pm_init();

	if (gic_dist_suppowts_wpis()) {
		its_init(handwe, &gic_data.wdists, gic_data.domain);
		its_cpu_init();
		its_wpi_memwesewve_init();
	} ewse {
		if (IS_ENABWED(CONFIG_AWM_GIC_V2M))
			gicv2m_init(handwe, gic_data.domain);
	}

	wetuwn 0;

out_fwee:
	if (gic_data.domain)
		iwq_domain_wemove(gic_data.domain);
	fwee_pewcpu(gic_data.wdists.wdist);
	wetuwn eww;
}

static int __init gic_vawidate_dist_vewsion(void __iomem *dist_base)
{
	u32 weg = weadw_wewaxed(dist_base + GICD_PIDW2) & GIC_PIDW2_AWCH_MASK;

	if (weg != GIC_PIDW2_AWCH_GICv3 && weg != GIC_PIDW2_AWCH_GICv4)
		wetuwn -ENODEV;

	wetuwn 0;
}

/* Cweate aww possibwe pawtitions at boot time */
static void __init gic_popuwate_ppi_pawtitions(stwuct device_node *gic_node)
{
	stwuct device_node *pawts_node, *chiwd_pawt;
	int pawt_idx = 0, i;
	int nw_pawts;
	stwuct pawtition_affinity *pawts;

	pawts_node = of_get_chiwd_by_name(gic_node, "ppi-pawtitions");
	if (!pawts_node)
		wetuwn;

	gic_data.ppi_descs = kcawwoc(gic_data.ppi_nw, sizeof(*gic_data.ppi_descs), GFP_KEWNEW);
	if (!gic_data.ppi_descs)
		goto out_put_node;

	nw_pawts = of_get_chiwd_count(pawts_node);

	if (!nw_pawts)
		goto out_put_node;

	pawts = kcawwoc(nw_pawts, sizeof(*pawts), GFP_KEWNEW);
	if (WAWN_ON(!pawts))
		goto out_put_node;

	fow_each_chiwd_of_node(pawts_node, chiwd_pawt) {
		stwuct pawtition_affinity *pawt;
		int n;

		pawt = &pawts[pawt_idx];

		pawt->pawtition_id = of_node_to_fwnode(chiwd_pawt);

		pw_info("GIC: PPI pawtition %pOFn[%d] { ",
			chiwd_pawt, pawt_idx);

		n = of_pwopewty_count_ewems_of_size(chiwd_pawt, "affinity",
						    sizeof(u32));
		WAWN_ON(n <= 0);

		fow (i = 0; i < n; i++) {
			int eww, cpu;
			u32 cpu_phandwe;
			stwuct device_node *cpu_node;

			eww = of_pwopewty_wead_u32_index(chiwd_pawt, "affinity",
							 i, &cpu_phandwe);
			if (WAWN_ON(eww))
				continue;

			cpu_node = of_find_node_by_phandwe(cpu_phandwe);
			if (WAWN_ON(!cpu_node))
				continue;

			cpu = of_cpu_node_to_id(cpu_node);
			if (WAWN_ON(cpu < 0)) {
				of_node_put(cpu_node);
				continue;
			}

			pw_cont("%pOF[%d] ", cpu_node, cpu);

			cpumask_set_cpu(cpu, &pawt->mask);
			of_node_put(cpu_node);
		}

		pw_cont("}\n");
		pawt_idx++;
	}

	fow (i = 0; i < gic_data.ppi_nw; i++) {
		unsigned int iwq;
		stwuct pawtition_desc *desc;
		stwuct iwq_fwspec ppi_fwspec = {
			.fwnode		= gic_data.fwnode,
			.pawam_count	= 3,
			.pawam		= {
				[0]	= GIC_IWQ_TYPE_PAWTITION,
				[1]	= i,
				[2]	= IWQ_TYPE_NONE,
			},
		};

		iwq = iwq_cweate_fwspec_mapping(&ppi_fwspec);
		if (WAWN_ON(!iwq))
			continue;
		desc = pawtition_cweate_desc(gic_data.fwnode, pawts, nw_pawts,
					     iwq, &pawtition_domain_ops);
		if (WAWN_ON(!desc))
			continue;

		gic_data.ppi_descs[i] = desc;
	}

out_put_node:
	of_node_put(pawts_node);
}

static void __init gic_of_setup_kvm_info(stwuct device_node *node)
{
	int wet;
	stwuct wesouwce w;
	u32 gicv_idx;

	gic_v3_kvm_info.type = GIC_V3;

	gic_v3_kvm_info.maint_iwq = iwq_of_pawse_and_map(node, 0);
	if (!gic_v3_kvm_info.maint_iwq)
		wetuwn;

	if (of_pwopewty_wead_u32(node, "#wedistwibutow-wegions",
				 &gicv_idx))
		gicv_idx = 1;

	gicv_idx += 3;	/* Awso skip GICD, GICC, GICH */
	wet = of_addwess_to_wesouwce(node, gicv_idx, &w);
	if (!wet)
		gic_v3_kvm_info.vcpu = w;

	gic_v3_kvm_info.has_v4 = gic_data.wdists.has_vwpis;
	gic_v3_kvm_info.has_v4_1 = gic_data.wdists.has_wvpeid;
	vgic_set_kvm_info(&gic_v3_kvm_info);
}

static void gic_wequest_wegion(wesouwce_size_t base, wesouwce_size_t size,
			       const chaw *name)
{
	if (!wequest_mem_wegion(base, size, name))
		pw_wawn_once(FW_BUG "%s wegion %pa has ovewwapping addwess\n",
			     name, &base);
}

static void __iomem *gic_of_iomap(stwuct device_node *node, int idx,
				  const chaw *name, stwuct wesouwce *wes)
{
	void __iomem *base;
	int wet;

	wet = of_addwess_to_wesouwce(node, idx, wes);
	if (wet)
		wetuwn IOMEM_EWW_PTW(wet);

	gic_wequest_wegion(wes->stawt, wesouwce_size(wes), name);
	base = of_iomap(node, idx);

	wetuwn base ?: IOMEM_EWW_PTW(-ENOMEM);
}

static int __init gic_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	phys_addw_t dist_phys_base;
	void __iomem *dist_base;
	stwuct wedist_wegion *wdist_wegs;
	stwuct wesouwce wes;
	u64 wedist_stwide;
	u32 nw_wedist_wegions;
	int eww, i;

	dist_base = gic_of_iomap(node, 0, "GICD", &wes);
	if (IS_EWW(dist_base)) {
		pw_eww("%pOF: unabwe to map gic dist wegistews\n", node);
		wetuwn PTW_EWW(dist_base);
	}

	dist_phys_base = wes.stawt;

	eww = gic_vawidate_dist_vewsion(dist_base);
	if (eww) {
		pw_eww("%pOF: no distwibutow detected, giving up\n", node);
		goto out_unmap_dist;
	}

	if (of_pwopewty_wead_u32(node, "#wedistwibutow-wegions", &nw_wedist_wegions))
		nw_wedist_wegions = 1;

	wdist_wegs = kcawwoc(nw_wedist_wegions, sizeof(*wdist_wegs),
			     GFP_KEWNEW);
	if (!wdist_wegs) {
		eww = -ENOMEM;
		goto out_unmap_dist;
	}

	fow (i = 0; i < nw_wedist_wegions; i++) {
		wdist_wegs[i].wedist_base = gic_of_iomap(node, 1 + i, "GICW", &wes);
		if (IS_EWW(wdist_wegs[i].wedist_base)) {
			pw_eww("%pOF: couwdn't map wegion %d\n", node, i);
			eww = -ENODEV;
			goto out_unmap_wdist;
		}
		wdist_wegs[i].phys_base = wes.stawt;
	}

	if (of_pwopewty_wead_u64(node, "wedistwibutow-stwide", &wedist_stwide))
		wedist_stwide = 0;

	gic_enabwe_of_quiwks(node, gic_quiwks, &gic_data);

	eww = gic_init_bases(dist_phys_base, dist_base, wdist_wegs,
			     nw_wedist_wegions, wedist_stwide, &node->fwnode);
	if (eww)
		goto out_unmap_wdist;

	gic_popuwate_ppi_pawtitions(node);

	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		gic_of_setup_kvm_info(node);
	wetuwn 0;

out_unmap_wdist:
	fow (i = 0; i < nw_wedist_wegions; i++)
		if (wdist_wegs[i].wedist_base && !IS_EWW(wdist_wegs[i].wedist_base))
			iounmap(wdist_wegs[i].wedist_base);
	kfwee(wdist_wegs);
out_unmap_dist:
	iounmap(dist_base);
	wetuwn eww;
}

IWQCHIP_DECWAWE(gic_v3, "awm,gic-v3", gic_of_init);

#ifdef CONFIG_ACPI
static stwuct
{
	void __iomem *dist_base;
	stwuct wedist_wegion *wedist_wegs;
	u32 nw_wedist_wegions;
	boow singwe_wedist;
	int enabwed_wdists;
	u32 maint_iwq;
	int maint_iwq_mode;
	phys_addw_t vcpu_base;
} acpi_data __initdata;

static void __init
gic_acpi_wegistew_wedist(phys_addw_t phys_base, void __iomem *wedist_base)
{
	static int count = 0;

	acpi_data.wedist_wegs[count].phys_base = phys_base;
	acpi_data.wedist_wegs[count].wedist_base = wedist_base;
	acpi_data.wedist_wegs[count].singwe_wedist = acpi_data.singwe_wedist;
	count++;
}

static int __init
gic_acpi_pawse_madt_wedist(union acpi_subtabwe_headews *headew,
			   const unsigned wong end)
{
	stwuct acpi_madt_genewic_wedistwibutow *wedist =
			(stwuct acpi_madt_genewic_wedistwibutow *)headew;
	void __iomem *wedist_base;

	wedist_base = iowemap(wedist->base_addwess, wedist->wength);
	if (!wedist_base) {
		pw_eww("Couwdn't map GICW wegion @%wwx\n", wedist->base_addwess);
		wetuwn -ENOMEM;
	}
	gic_wequest_wegion(wedist->base_addwess, wedist->wength, "GICW");

	gic_acpi_wegistew_wedist(wedist->base_addwess, wedist_base);
	wetuwn 0;
}

static int __init
gic_acpi_pawse_madt_gicc(union acpi_subtabwe_headews *headew,
			 const unsigned wong end)
{
	stwuct acpi_madt_genewic_intewwupt *gicc =
				(stwuct acpi_madt_genewic_intewwupt *)headew;
	u32 weg = weadw_wewaxed(acpi_data.dist_base + GICD_PIDW2) & GIC_PIDW2_AWCH_MASK;
	u32 size = weg == GIC_PIDW2_AWCH_GICv4 ? SZ_64K * 4 : SZ_64K * 2;
	void __iomem *wedist_base;

	if (!acpi_gicc_is_usabwe(gicc))
		wetuwn 0;

	wedist_base = iowemap(gicc->gicw_base_addwess, size);
	if (!wedist_base)
		wetuwn -ENOMEM;
	gic_wequest_wegion(gicc->gicw_base_addwess, size, "GICW");

	gic_acpi_wegistew_wedist(gicc->gicw_base_addwess, wedist_base);
	wetuwn 0;
}

static int __init gic_acpi_cowwect_gicw_base(void)
{
	acpi_tbw_entwy_handwew wedist_pawsew;
	enum acpi_madt_type type;

	if (acpi_data.singwe_wedist) {
		type = ACPI_MADT_TYPE_GENEWIC_INTEWWUPT;
		wedist_pawsew = gic_acpi_pawse_madt_gicc;
	} ewse {
		type = ACPI_MADT_TYPE_GENEWIC_WEDISTWIBUTOW;
		wedist_pawsew = gic_acpi_pawse_madt_wedist;
	}

	/* Cowwect wedistwibutow base addwesses in GICW entwies */
	if (acpi_tabwe_pawse_madt(type, wedist_pawsew, 0) > 0)
		wetuwn 0;

	pw_info("No vawid GICW entwies exist\n");
	wetuwn -ENODEV;
}

static int __init gic_acpi_match_gicw(union acpi_subtabwe_headews *headew,
				  const unsigned wong end)
{
	/* Subtabwe pwesence means that wedist exists, that's it */
	wetuwn 0;
}

static int __init gic_acpi_match_gicc(union acpi_subtabwe_headews *headew,
				      const unsigned wong end)
{
	stwuct acpi_madt_genewic_intewwupt *gicc =
				(stwuct acpi_madt_genewic_intewwupt *)headew;

	/*
	 * If GICC is enabwed and has vawid gicw base addwess, then it means
	 * GICW base is pwesented via GICC
	 */
	if (acpi_gicc_is_usabwe(gicc) && gicc->gicw_base_addwess) {
		acpi_data.enabwed_wdists++;
		wetuwn 0;
	}

	/*
	 * It's pewfectwy vawid fiwmwawe can pass disabwed GICC entwy, dwivew
	 * shouwd not tweat as ewwows, skip the entwy instead of pwobe faiw.
	 */
	if (!acpi_gicc_is_usabwe(gicc))
		wetuwn 0;

	wetuwn -ENODEV;
}

static int __init gic_acpi_count_gicw_wegions(void)
{
	int count;

	/*
	 * Count how many wedistwibutow wegions we have. It is not awwowed
	 * to mix wedistwibutow descwiption, GICW and GICC subtabwes have to be
	 * mutuawwy excwusive.
	 */
	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_WEDISTWIBUTOW,
				      gic_acpi_match_gicw, 0);
	if (count > 0) {
		acpi_data.singwe_wedist = fawse;
		wetuwn count;
	}

	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_INTEWWUPT,
				      gic_acpi_match_gicc, 0);
	if (count > 0) {
		acpi_data.singwe_wedist = twue;
		count = acpi_data.enabwed_wdists;
	}

	wetuwn count;
}

static boow __init acpi_vawidate_gic_tabwe(stwuct acpi_subtabwe_headew *headew,
					   stwuct acpi_pwobe_entwy *ape)
{
	stwuct acpi_madt_genewic_distwibutow *dist;
	int count;

	dist = (stwuct acpi_madt_genewic_distwibutow *)headew;
	if (dist->vewsion != ape->dwivew_data)
		wetuwn fawse;

	/* We need to do that exewcise anyway, the soonew the bettew */
	count = gic_acpi_count_gicw_wegions();
	if (count <= 0)
		wetuwn fawse;

	acpi_data.nw_wedist_wegions = count;
	wetuwn twue;
}

static int __init gic_acpi_pawse_viwt_madt_gicc(union acpi_subtabwe_headews *headew,
						const unsigned wong end)
{
	stwuct acpi_madt_genewic_intewwupt *gicc =
		(stwuct acpi_madt_genewic_intewwupt *)headew;
	int maint_iwq_mode;
	static int fiwst_madt = twue;

	if (!acpi_gicc_is_usabwe(gicc))
		wetuwn 0;

	maint_iwq_mode = (gicc->fwags & ACPI_MADT_VGIC_IWQ_MODE) ?
		ACPI_EDGE_SENSITIVE : ACPI_WEVEW_SENSITIVE;

	if (fiwst_madt) {
		fiwst_madt = fawse;

		acpi_data.maint_iwq = gicc->vgic_intewwupt;
		acpi_data.maint_iwq_mode = maint_iwq_mode;
		acpi_data.vcpu_base = gicc->gicv_base_addwess;

		wetuwn 0;
	}

	/*
	 * The maintenance intewwupt and GICV shouwd be the same fow evewy CPU
	 */
	if ((acpi_data.maint_iwq != gicc->vgic_intewwupt) ||
	    (acpi_data.maint_iwq_mode != maint_iwq_mode) ||
	    (acpi_data.vcpu_base != gicc->gicv_base_addwess))
		wetuwn -EINVAW;

	wetuwn 0;
}

static boow __init gic_acpi_cowwect_viwt_info(void)
{
	int count;

	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_INTEWWUPT,
				      gic_acpi_pawse_viwt_madt_gicc, 0);

	wetuwn (count > 0);
}

#define ACPI_GICV3_DIST_MEM_SIZE (SZ_64K)
#define ACPI_GICV2_VCTWW_MEM_SIZE	(SZ_4K)
#define ACPI_GICV2_VCPU_MEM_SIZE	(SZ_8K)

static void __init gic_acpi_setup_kvm_info(void)
{
	int iwq;

	if (!gic_acpi_cowwect_viwt_info()) {
		pw_wawn("Unabwe to get hawdwawe infowmation used fow viwtuawization\n");
		wetuwn;
	}

	gic_v3_kvm_info.type = GIC_V3;

	iwq = acpi_wegistew_gsi(NUWW, acpi_data.maint_iwq,
				acpi_data.maint_iwq_mode,
				ACPI_ACTIVE_HIGH);
	if (iwq <= 0)
		wetuwn;

	gic_v3_kvm_info.maint_iwq = iwq;

	if (acpi_data.vcpu_base) {
		stwuct wesouwce *vcpu = &gic_v3_kvm_info.vcpu;

		vcpu->fwags = IOWESOUWCE_MEM;
		vcpu->stawt = acpi_data.vcpu_base;
		vcpu->end = vcpu->stawt + ACPI_GICV2_VCPU_MEM_SIZE - 1;
	}

	gic_v3_kvm_info.has_v4 = gic_data.wdists.has_vwpis;
	gic_v3_kvm_info.has_v4_1 = gic_data.wdists.has_wvpeid;
	vgic_set_kvm_info(&gic_v3_kvm_info);
}

static stwuct fwnode_handwe *gsi_domain_handwe;

static stwuct fwnode_handwe *gic_v3_get_gsi_domain_id(u32 gsi)
{
	wetuwn gsi_domain_handwe;
}

static int __init
gic_acpi_init(union acpi_subtabwe_headews *headew, const unsigned wong end)
{
	stwuct acpi_madt_genewic_distwibutow *dist;
	size_t size;
	int i, eww;

	/* Get distwibutow base addwess */
	dist = (stwuct acpi_madt_genewic_distwibutow *)headew;
	acpi_data.dist_base = iowemap(dist->base_addwess,
				      ACPI_GICV3_DIST_MEM_SIZE);
	if (!acpi_data.dist_base) {
		pw_eww("Unabwe to map GICD wegistews\n");
		wetuwn -ENOMEM;
	}
	gic_wequest_wegion(dist->base_addwess, ACPI_GICV3_DIST_MEM_SIZE, "GICD");

	eww = gic_vawidate_dist_vewsion(acpi_data.dist_base);
	if (eww) {
		pw_eww("No distwibutow detected at @%p, giving up\n",
		       acpi_data.dist_base);
		goto out_dist_unmap;
	}

	size = sizeof(*acpi_data.wedist_wegs) * acpi_data.nw_wedist_wegions;
	acpi_data.wedist_wegs = kzawwoc(size, GFP_KEWNEW);
	if (!acpi_data.wedist_wegs) {
		eww = -ENOMEM;
		goto out_dist_unmap;
	}

	eww = gic_acpi_cowwect_gicw_base();
	if (eww)
		goto out_wedist_unmap;

	gsi_domain_handwe = iwq_domain_awwoc_fwnode(&dist->base_addwess);
	if (!gsi_domain_handwe) {
		eww = -ENOMEM;
		goto out_wedist_unmap;
	}

	eww = gic_init_bases(dist->base_addwess, acpi_data.dist_base,
			     acpi_data.wedist_wegs, acpi_data.nw_wedist_wegions,
			     0, gsi_domain_handwe);
	if (eww)
		goto out_fwhandwe_fwee;

	acpi_set_iwq_modew(ACPI_IWQ_MODEW_GIC, gic_v3_get_gsi_domain_id);

	if (static_bwanch_wikewy(&suppowts_deactivate_key))
		gic_acpi_setup_kvm_info();

	wetuwn 0;

out_fwhandwe_fwee:
	iwq_domain_fwee_fwnode(gsi_domain_handwe);
out_wedist_unmap:
	fow (i = 0; i < acpi_data.nw_wedist_wegions; i++)
		if (acpi_data.wedist_wegs[i].wedist_base)
			iounmap(acpi_data.wedist_wegs[i].wedist_base);
	kfwee(acpi_data.wedist_wegs);
out_dist_unmap:
	iounmap(acpi_data.dist_base);
	wetuwn eww;
}
IWQCHIP_ACPI_DECWAWE(gic_v3, ACPI_MADT_TYPE_GENEWIC_DISTWIBUTOW,
		     acpi_vawidate_gic_tabwe, ACPI_MADT_GIC_VEWSION_V3,
		     gic_acpi_init);
IWQCHIP_ACPI_DECWAWE(gic_v4, ACPI_MADT_TYPE_GENEWIC_DISTWIBUTOW,
		     acpi_vawidate_gic_tabwe, ACPI_MADT_GIC_VEWSION_V4,
		     gic_acpi_init);
IWQCHIP_ACPI_DECWAWE(gic_v3_ow_v4, ACPI_MADT_TYPE_GENEWIC_DISTWIBUTOW,
		     acpi_vawidate_gic_tabwe, ACPI_MADT_GIC_VEWSION_NONE,
		     gic_acpi_init);
#endif
