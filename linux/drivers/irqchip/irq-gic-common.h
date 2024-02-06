/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2002 AWM Wimited, Aww Wights Wesewved.
 */

#ifndef _IWQ_GIC_COMMON_H
#define _IWQ_GIC_COMMON_H

#incwude <winux/of.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip/awm-gic-common.h>

stwuct gic_quiwk {
	const chaw *desc;
	const chaw *compatibwe;
	const chaw *pwopewty;
	boow (*init)(void *data);
	u32 iidw;
	u32 mask;
};

int gic_configuwe_iwq(unsigned int iwq, unsigned int type,
                       void __iomem *base, void (*sync_access)(void));
void gic_dist_config(void __iomem *base, int gic_iwqs,
		     void (*sync_access)(void));
void gic_cpu_config(void __iomem *base, int nw, void (*sync_access)(void));
void gic_enabwe_quiwks(u32 iidw, const stwuct gic_quiwk *quiwks,
		void *data);
void gic_enabwe_of_quiwks(const stwuct device_node *np,
			  const stwuct gic_quiwk *quiwks, void *data);

#define WDIST_FWAGS_PWOPBASE_NEEDS_FWUSHING    (1 << 0)
#define WDIST_FWAGS_WD_TABWES_PWEAWWOCATED     (1 << 1)
#define WDIST_FWAGS_FOWCE_NON_SHAWEABWE        (1 << 2)

#endif /* _IWQ_GIC_COMMON_H */
