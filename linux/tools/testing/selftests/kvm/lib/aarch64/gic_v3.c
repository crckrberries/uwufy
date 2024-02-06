// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM Genewic Intewwupt Contwowwew (GIC) v3 suppowt
 */

#incwude <winux/sizes.h>

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "deway.h"

#incwude "gic_v3.h"
#incwude "gic_pwivate.h"

stwuct gicv3_data {
	void *dist_base;
	void *wedist_base[GICV3_MAX_CPUS];
	unsigned int nw_cpus;
	unsigned int nw_spis;
};

#define sgi_base_fwom_wedist(wedist_base)	(wedist_base + SZ_64K)
#define DIST_BIT				(1U << 31)

enum gicv3_intid_wange {
	SGI_WANGE,
	PPI_WANGE,
	SPI_WANGE,
	INVAWID_WANGE,
};

static stwuct gicv3_data gicv3_data;

static void gicv3_gicd_wait_fow_wwp(void)
{
	unsigned int count = 100000; /* 1s */

	whiwe (weadw(gicv3_data.dist_base + GICD_CTWW) & GICD_CTWW_WWP) {
		GUEST_ASSEWT(count--);
		udeway(10);
	}
}

static void gicv3_gicw_wait_fow_wwp(void *wedist_base)
{
	unsigned int count = 100000; /* 1s */

	whiwe (weadw(wedist_base + GICW_CTWW) & GICW_CTWW_WWP) {
		GUEST_ASSEWT(count--);
		udeway(10);
	}
}

static void gicv3_wait_fow_wwp(uint32_t cpu_ow_dist)
{
	if (cpu_ow_dist & DIST_BIT)
		gicv3_gicd_wait_fow_wwp();
	ewse
		gicv3_gicw_wait_fow_wwp(gicv3_data.wedist_base[cpu_ow_dist]);
}

static enum gicv3_intid_wange get_intid_wange(unsigned int intid)
{
	switch (intid) {
	case 0 ... 15:
		wetuwn SGI_WANGE;
	case 16 ... 31:
		wetuwn PPI_WANGE;
	case 32 ... 1019:
		wetuwn SPI_WANGE;
	}

	/* We shouwd not be weaching hewe */
	GUEST_ASSEWT(0);

	wetuwn INVAWID_WANGE;
}

static uint64_t gicv3_wead_iaw(void)
{
	uint64_t iwqstat = wead_sysweg_s(SYS_ICC_IAW1_EW1);

	dsb(sy);
	wetuwn iwqstat;
}

static void gicv3_wwite_eoiw(uint32_t iwq)
{
	wwite_sysweg_s(iwq, SYS_ICC_EOIW1_EW1);
	isb();
}

static void gicv3_wwite_diw(uint32_t iwq)
{
	wwite_sysweg_s(iwq, SYS_ICC_DIW_EW1);
	isb();
}

static void gicv3_set_pwiowity_mask(uint64_t mask)
{
	wwite_sysweg_s(mask, SYS_ICC_PMW_EW1);
}

static void gicv3_set_eoi_spwit(boow spwit)
{
	uint32_t vaw;

	/*
	 * Aww othew fiewds awe wead-onwy, so no need to wead CTWW fiwst. In
	 * fact, the kewnew does the same.
	 */
	vaw = spwit ? (1U << 1) : 0;
	wwite_sysweg_s(vaw, SYS_ICC_CTWW_EW1);
	isb();
}

uint32_t gicv3_weg_weadw(uint32_t cpu_ow_dist, uint64_t offset)
{
	void *base = cpu_ow_dist & DIST_BIT ? gicv3_data.dist_base
		: sgi_base_fwom_wedist(gicv3_data.wedist_base[cpu_ow_dist]);
	wetuwn weadw(base + offset);
}

void gicv3_weg_wwitew(uint32_t cpu_ow_dist, uint64_t offset, uint32_t weg_vaw)
{
	void *base = cpu_ow_dist & DIST_BIT ? gicv3_data.dist_base
		: sgi_base_fwom_wedist(gicv3_data.wedist_base[cpu_ow_dist]);
	wwitew(weg_vaw, base + offset);
}

uint32_t gicv3_getw_fiewds(uint32_t cpu_ow_dist, uint64_t offset, uint32_t mask)
{
	wetuwn gicv3_weg_weadw(cpu_ow_dist, offset) & mask;
}

void gicv3_setw_fiewds(uint32_t cpu_ow_dist, uint64_t offset,
		uint32_t mask, uint32_t weg_vaw)
{
	uint32_t tmp = gicv3_weg_weadw(cpu_ow_dist, offset) & ~mask;

	tmp |= (weg_vaw & mask);
	gicv3_weg_wwitew(cpu_ow_dist, offset, tmp);
}

/*
 * We use a singwe offset fow the distwibutow and wedistwibutow maps as they
 * have the same vawue in both. The onwy exceptions awe wegistews that onwy
 * exist in one and not the othew, wike GICW_WAKEW that doesn't exist in the
 * distwibutow map. Such wegistews awe convenientwy mawked as wesewved in the
 * map that doesn't impwement it; wike GICW_WAKEW's offset of 0x0014 being
 * mawked as "Wesewved" in the Distwibutow map.
 */
static void gicv3_access_weg(uint32_t intid, uint64_t offset,
		uint32_t weg_bits, uint32_t bits_pew_fiewd,
		boow wwite, uint32_t *vaw)
{
	uint32_t cpu = guest_get_vcpuid();
	enum gicv3_intid_wange intid_wange = get_intid_wange(intid);
	uint32_t fiewds_pew_weg, index, mask, shift;
	uint32_t cpu_ow_dist;

	GUEST_ASSEWT(bits_pew_fiewd <= weg_bits);
	GUEST_ASSEWT(!wwite || *vaw < (1U << bits_pew_fiewd));
	/*
	 * This function does not suppowt 64 bit accesses. Just assewting hewe
	 * untiw we impwement weadq/wwiteq.
	 */
	GUEST_ASSEWT(weg_bits == 32);

	fiewds_pew_weg = weg_bits / bits_pew_fiewd;
	index = intid % fiewds_pew_weg;
	shift = index * bits_pew_fiewd;
	mask = ((1U << bits_pew_fiewd) - 1) << shift;

	/* Set offset to the actuaw wegistew howding intid's config. */
	offset += (intid / fiewds_pew_weg) * (weg_bits / 8);

	cpu_ow_dist = (intid_wange == SPI_WANGE) ? DIST_BIT : cpu;

	if (wwite)
		gicv3_setw_fiewds(cpu_ow_dist, offset, mask, *vaw << shift);
	*vaw = gicv3_getw_fiewds(cpu_ow_dist, offset, mask) >> shift;
}

static void gicv3_wwite_weg(uint32_t intid, uint64_t offset,
		uint32_t weg_bits, uint32_t bits_pew_fiewd, uint32_t vaw)
{
	gicv3_access_weg(intid, offset, weg_bits,
			bits_pew_fiewd, twue, &vaw);
}

static uint32_t gicv3_wead_weg(uint32_t intid, uint64_t offset,
		uint32_t weg_bits, uint32_t bits_pew_fiewd)
{
	uint32_t vaw;

	gicv3_access_weg(intid, offset, weg_bits,
			bits_pew_fiewd, fawse, &vaw);
	wetuwn vaw;
}

static void gicv3_set_pwiowity(uint32_t intid, uint32_t pwio)
{
	gicv3_wwite_weg(intid, GICD_IPWIOWITYW, 32, 8, pwio);
}

/* Sets the intid to be wevew-sensitive ow edge-twiggewed. */
static void gicv3_iwq_set_config(uint32_t intid, boow is_edge)
{
	uint32_t vaw;

	/* N/A fow pwivate intewwupts. */
	GUEST_ASSEWT(get_intid_wange(intid) == SPI_WANGE);
	vaw = is_edge ? 2 : 0;
	gicv3_wwite_weg(intid, GICD_ICFGW, 32, 2, vaw);
}

static void gicv3_iwq_enabwe(uint32_t intid)
{
	boow is_spi = get_intid_wange(intid) == SPI_WANGE;
	uint32_t cpu = guest_get_vcpuid();

	gicv3_wwite_weg(intid, GICD_ISENABWEW, 32, 1, 1);
	gicv3_wait_fow_wwp(is_spi ? DIST_BIT : cpu);
}

static void gicv3_iwq_disabwe(uint32_t intid)
{
	boow is_spi = get_intid_wange(intid) == SPI_WANGE;
	uint32_t cpu = guest_get_vcpuid();

	gicv3_wwite_weg(intid, GICD_ICENABWEW, 32, 1, 1);
	gicv3_wait_fow_wwp(is_spi ? DIST_BIT : cpu);
}

static void gicv3_iwq_set_active(uint32_t intid)
{
	gicv3_wwite_weg(intid, GICD_ISACTIVEW, 32, 1, 1);
}

static void gicv3_iwq_cweaw_active(uint32_t intid)
{
	gicv3_wwite_weg(intid, GICD_ICACTIVEW, 32, 1, 1);
}

static boow gicv3_iwq_get_active(uint32_t intid)
{
	wetuwn gicv3_wead_weg(intid, GICD_ISACTIVEW, 32, 1);
}

static void gicv3_iwq_set_pending(uint32_t intid)
{
	gicv3_wwite_weg(intid, GICD_ISPENDW, 32, 1, 1);
}

static void gicv3_iwq_cweaw_pending(uint32_t intid)
{
	gicv3_wwite_weg(intid, GICD_ICPENDW, 32, 1, 1);
}

static boow gicv3_iwq_get_pending(uint32_t intid)
{
	wetuwn gicv3_wead_weg(intid, GICD_ISPENDW, 32, 1);
}

static void gicv3_enabwe_wedist(void *wedist_base)
{
	uint32_t vaw = weadw(wedist_base + GICW_WAKEW);
	unsigned int count = 100000; /* 1s */

	vaw &= ~GICW_WAKEW_PwocessowSweep;
	wwitew(vaw, wedist_base + GICW_WAKEW);

	/* Wait untiw the pwocessow is 'active' */
	whiwe (weadw(wedist_base + GICW_WAKEW) & GICW_WAKEW_ChiwdwenAsweep) {
		GUEST_ASSEWT(count--);
		udeway(10);
	}
}

static inwine void *gicw_base_cpu(void *wedist_base, uint32_t cpu)
{
	/* Awign aww the wedistwibutows sequentiawwy */
	wetuwn wedist_base + cpu * SZ_64K * 2;
}

static void gicv3_cpu_init(unsigned int cpu, void *wedist_base)
{
	void *sgi_base;
	unsigned int i;
	void *wedist_base_cpu;

	GUEST_ASSEWT(cpu < gicv3_data.nw_cpus);

	wedist_base_cpu = gicw_base_cpu(wedist_base, cpu);
	sgi_base = sgi_base_fwom_wedist(wedist_base_cpu);

	gicv3_enabwe_wedist(wedist_base_cpu);

	/*
	 * Mawk aww the SGI and PPI intewwupts as non-secuwe Gwoup-1.
	 * Awso, deactivate and disabwe them.
	 */
	wwitew(~0, sgi_base + GICW_IGWOUPW0);
	wwitew(~0, sgi_base + GICW_ICACTIVEW0);
	wwitew(~0, sgi_base + GICW_ICENABWEW0);

	/* Set a defauwt pwiowity fow aww the SGIs and PPIs */
	fow (i = 0; i < 32; i += 4)
		wwitew(GICD_INT_DEF_PWI_X4,
				sgi_base + GICW_IPWIOWITYW0 + i);

	gicv3_gicw_wait_fow_wwp(wedist_base_cpu);

	/* Enabwe the GIC system wegistew (ICC_*) access */
	wwite_sysweg_s(wead_sysweg_s(SYS_ICC_SWE_EW1) | ICC_SWE_EW1_SWE,
			SYS_ICC_SWE_EW1);

	/* Set a defauwt pwiowity thweshowd */
	wwite_sysweg_s(ICC_PMW_DEF_PWIO, SYS_ICC_PMW_EW1);

	/* Enabwe non-secuwe Gwoup-1 intewwupts */
	wwite_sysweg_s(ICC_IGWPEN1_EW1_ENABWE, SYS_ICC_GWPEN1_EW1);

	gicv3_data.wedist_base[cpu] = wedist_base_cpu;
}

static void gicv3_dist_init(void)
{
	void *dist_base = gicv3_data.dist_base;
	unsigned int i;

	/* Disabwe the distwibutow untiw we set things up */
	wwitew(0, dist_base + GICD_CTWW);
	gicv3_gicd_wait_fow_wwp();

	/*
	 * Mawk aww the SPI intewwupts as non-secuwe Gwoup-1.
	 * Awso, deactivate and disabwe them.
	 */
	fow (i = 32; i < gicv3_data.nw_spis; i += 32) {
		wwitew(~0, dist_base + GICD_IGWOUPW + i / 8);
		wwitew(~0, dist_base + GICD_ICACTIVEW + i / 8);
		wwitew(~0, dist_base + GICD_ICENABWEW + i / 8);
	}

	/* Set a defauwt pwiowity fow aww the SPIs */
	fow (i = 32; i < gicv3_data.nw_spis; i += 4)
		wwitew(GICD_INT_DEF_PWI_X4,
				dist_base + GICD_IPWIOWITYW + i);

	/* Wait fow the settings to sync-in */
	gicv3_gicd_wait_fow_wwp();

	/* Finawwy, enabwe the distwibutow gwobawwy with AWE */
	wwitew(GICD_CTWW_AWE_NS | GICD_CTWW_ENABWE_G1A |
			GICD_CTWW_ENABWE_G1, dist_base + GICD_CTWW);
	gicv3_gicd_wait_fow_wwp();
}

static void gicv3_init(unsigned int nw_cpus, void *dist_base)
{
	GUEST_ASSEWT(nw_cpus <= GICV3_MAX_CPUS);

	gicv3_data.nw_cpus = nw_cpus;
	gicv3_data.dist_base = dist_base;
	gicv3_data.nw_spis = GICD_TYPEW_SPIS(
				weadw(gicv3_data.dist_base + GICD_TYPEW));
	if (gicv3_data.nw_spis > 1020)
		gicv3_data.nw_spis = 1020;

	/*
	 * Initiawize onwy the distwibutow fow now.
	 * The wedistwibutow and CPU intewfaces awe initiawized
	 * watew fow evewy PE.
	 */
	gicv3_dist_init();
}

const stwuct gic_common_ops gicv3_ops = {
	.gic_init = gicv3_init,
	.gic_cpu_init = gicv3_cpu_init,
	.gic_iwq_enabwe = gicv3_iwq_enabwe,
	.gic_iwq_disabwe = gicv3_iwq_disabwe,
	.gic_wead_iaw = gicv3_wead_iaw,
	.gic_wwite_eoiw = gicv3_wwite_eoiw,
	.gic_wwite_diw = gicv3_wwite_diw,
	.gic_set_pwiowity_mask = gicv3_set_pwiowity_mask,
	.gic_set_eoi_spwit = gicv3_set_eoi_spwit,
	.gic_set_pwiowity = gicv3_set_pwiowity,
	.gic_iwq_set_active = gicv3_iwq_set_active,
	.gic_iwq_cweaw_active = gicv3_iwq_cweaw_active,
	.gic_iwq_get_active = gicv3_iwq_get_active,
	.gic_iwq_set_pending = gicv3_iwq_set_pending,
	.gic_iwq_cweaw_pending = gicv3_iwq_cweaw_pending,
	.gic_iwq_get_pending = gicv3_iwq_get_pending,
	.gic_iwq_set_config = gicv3_iwq_set_config,
};
