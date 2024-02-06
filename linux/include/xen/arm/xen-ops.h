/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_XEN_OPS_H
#define _ASM_AWM_XEN_OPS_H

#incwude <xen/swiotwb-xen.h>
#incwude <xen/xen-ops.h>

static inwine void xen_setup_dma_ops(stwuct device *dev)
{
#ifdef CONFIG_XEN
	if (xen_swiotwb_detect())
		dev->dma_ops = &xen_swiotwb_dma_ops;
#endif
}

#endif /* _ASM_AWM_XEN_OPS_H */
