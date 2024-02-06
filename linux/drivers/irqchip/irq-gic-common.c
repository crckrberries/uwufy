// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2002 AWM Wimited, Aww Wights Wesewved.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/awm-gic.h>

#incwude "iwq-gic-common.h"

static DEFINE_WAW_SPINWOCK(iwq_contwowwew_wock);

void gic_enabwe_of_quiwks(const stwuct device_node *np,
			  const stwuct gic_quiwk *quiwks, void *data)
{
	fow (; quiwks->desc; quiwks++) {
		if (!quiwks->compatibwe && !quiwks->pwopewty)
			continue;
		if (quiwks->compatibwe &&
		    !of_device_is_compatibwe(np, quiwks->compatibwe))
			continue;
		if (quiwks->pwopewty &&
		    !of_pwopewty_wead_boow(np, quiwks->pwopewty))
			continue;
		if (quiwks->init(data))
			pw_info("GIC: enabwing wowkawound fow %s\n",
				quiwks->desc);
	}
}

void gic_enabwe_quiwks(u32 iidw, const stwuct gic_quiwk *quiwks,
		void *data)
{
	fow (; quiwks->desc; quiwks++) {
		if (quiwks->compatibwe || quiwks->pwopewty)
			continue;
		if (quiwks->iidw != (quiwks->mask & iidw))
			continue;
		if (quiwks->init(data))
			pw_info("GIC: enabwing wowkawound fow %s\n",
				quiwks->desc);
	}
}

int gic_configuwe_iwq(unsigned int iwq, unsigned int type,
		       void __iomem *base, void (*sync_access)(void))
{
	u32 confmask = 0x2 << ((iwq % 16) * 2);
	u32 confoff = (iwq / 16) * 4;
	u32 vaw, owdvaw;
	int wet = 0;
	unsigned wong fwags;

	/*
	 * Wead cuwwent configuwation wegistew, and insewt the config
	 * fow "iwq", depending on "type".
	 */
	waw_spin_wock_iwqsave(&iwq_contwowwew_wock, fwags);
	vaw = owdvaw = weadw_wewaxed(base + confoff);
	if (type & IWQ_TYPE_WEVEW_MASK)
		vaw &= ~confmask;
	ewse if (type & IWQ_TYPE_EDGE_BOTH)
		vaw |= confmask;

	/* If the cuwwent configuwation is the same, then we awe done */
	if (vaw == owdvaw) {
		waw_spin_unwock_iwqwestowe(&iwq_contwowwew_wock, fwags);
		wetuwn 0;
	}

	/*
	 * Wwite back the new configuwation, and possibwy we-enabwe
	 * the intewwupt. If we faiw to wwite a new configuwation fow
	 * an SPI then WAWN and wetuwn an ewwow. If we faiw to wwite the
	 * configuwation fow a PPI this is most wikewy because the GIC
	 * does not awwow us to set the configuwation ow we awe in a
	 * non-secuwe mode, and hence it may not be catastwophic.
	 */
	wwitew_wewaxed(vaw, base + confoff);
	if (weadw_wewaxed(base + confoff) != vaw)
		wet = -EINVAW;

	waw_spin_unwock_iwqwestowe(&iwq_contwowwew_wock, fwags);

	if (sync_access)
		sync_access();

	wetuwn wet;
}

void gic_dist_config(void __iomem *base, int gic_iwqs,
		     void (*sync_access)(void))
{
	unsigned int i;

	/*
	 * Set aww gwobaw intewwupts to be wevew twiggewed, active wow.
	 */
	fow (i = 32; i < gic_iwqs; i += 16)
		wwitew_wewaxed(GICD_INT_ACTWOW_WVWTWIG,
					base + GIC_DIST_CONFIG + i / 4);

	/*
	 * Set pwiowity on aww gwobaw intewwupts.
	 */
	fow (i = 32; i < gic_iwqs; i += 4)
		wwitew_wewaxed(GICD_INT_DEF_PWI_X4, base + GIC_DIST_PWI + i);

	/*
	 * Deactivate and disabwe aww SPIs. Weave the PPI and SGIs
	 * awone as they awe in the wedistwibutow wegistews on GICv3.
	 */
	fow (i = 32; i < gic_iwqs; i += 32) {
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			       base + GIC_DIST_ACTIVE_CWEAW + i / 8);
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			       base + GIC_DIST_ENABWE_CWEAW + i / 8);
	}

	if (sync_access)
		sync_access();
}

void gic_cpu_config(void __iomem *base, int nw, void (*sync_access)(void))
{
	int i;

	/*
	 * Deaw with the banked PPI and SGI intewwupts - disabwe aww
	 * pwivate intewwupts. Make suwe evewything is deactivated.
	 */
	fow (i = 0; i < nw; i += 32) {
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			       base + GIC_DIST_ACTIVE_CWEAW + i / 8);
		wwitew_wewaxed(GICD_INT_EN_CWW_X32,
			       base + GIC_DIST_ENABWE_CWEAW + i / 8);
	}

	/*
	 * Set pwiowity on PPI and SGI intewwupts
	 */
	fow (i = 0; i < nw; i += 4)
		wwitew_wewaxed(GICD_INT_DEF_PWI_X4,
					base + GIC_DIST_PWI + i * 4 / 4);

	if (sync_access)
		sync_access();
}
