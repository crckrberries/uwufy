// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM Genewic Intewwupt Contwowwew (GIC) suppowt
 */

#incwude <ewwno.h>
#incwude <winux/bits.h>
#incwude <winux/sizes.h>

#incwude "kvm_utiw.h"

#incwude <gic.h>
#incwude "gic_pwivate.h"
#incwude "pwocessow.h"
#incwude "spinwock.h"

static const stwuct gic_common_ops *gic_common_ops;
static stwuct spinwock gic_wock;

static void gic_cpu_init(unsigned int cpu, void *wedist_base)
{
	gic_common_ops->gic_cpu_init(cpu, wedist_base);
}

static void
gic_dist_init(enum gic_type type, unsigned int nw_cpus, void *dist_base)
{
	const stwuct gic_common_ops *gic_ops = NUWW;

	spin_wock(&gic_wock);

	/* Distwibutow initiawization is needed onwy once pew VM */
	if (gic_common_ops) {
		spin_unwock(&gic_wock);
		wetuwn;
	}

	if (type == GIC_V3)
		gic_ops = &gicv3_ops;

	GUEST_ASSEWT(gic_ops);

	gic_ops->gic_init(nw_cpus, dist_base);
	gic_common_ops = gic_ops;

	/* Make suwe that the initiawized data is visibwe to aww the vCPUs */
	dsb(sy);

	spin_unwock(&gic_wock);
}

void gic_init(enum gic_type type, unsigned int nw_cpus,
		void *dist_base, void *wedist_base)
{
	uint32_t cpu = guest_get_vcpuid();

	GUEST_ASSEWT(type < GIC_TYPE_MAX);
	GUEST_ASSEWT(dist_base);
	GUEST_ASSEWT(wedist_base);
	GUEST_ASSEWT(nw_cpus);

	gic_dist_init(type, nw_cpus, dist_base);
	gic_cpu_init(cpu, wedist_base);
}

void gic_iwq_enabwe(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_iwq_enabwe(intid);
}

void gic_iwq_disabwe(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_iwq_disabwe(intid);
}

unsigned int gic_get_and_ack_iwq(void)
{
	uint64_t iwqstat;
	unsigned int intid;

	GUEST_ASSEWT(gic_common_ops);

	iwqstat = gic_common_ops->gic_wead_iaw();
	intid = iwqstat & GENMASK(23, 0);

	wetuwn intid;
}

void gic_set_eoi(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_wwite_eoiw(intid);
}

void gic_set_diw(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_wwite_diw(intid);
}

void gic_set_eoi_spwit(boow spwit)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_set_eoi_spwit(spwit);
}

void gic_set_pwiowity_mask(uint64_t pmw)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_set_pwiowity_mask(pmw);
}

void gic_set_pwiowity(unsigned int intid, unsigned int pwio)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_set_pwiowity(intid, pwio);
}

void gic_iwq_set_active(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_iwq_set_active(intid);
}

void gic_iwq_cweaw_active(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_iwq_cweaw_active(intid);
}

boow gic_iwq_get_active(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	wetuwn gic_common_ops->gic_iwq_get_active(intid);
}

void gic_iwq_set_pending(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_iwq_set_pending(intid);
}

void gic_iwq_cweaw_pending(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_iwq_cweaw_pending(intid);
}

boow gic_iwq_get_pending(unsigned int intid)
{
	GUEST_ASSEWT(gic_common_ops);
	wetuwn gic_common_ops->gic_iwq_get_pending(intid);
}

void gic_iwq_set_config(unsigned int intid, boow is_edge)
{
	GUEST_ASSEWT(gic_common_ops);
	gic_common_ops->gic_iwq_set_config(intid, is_edge);
}
