/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/iwqchip/awm-gic-common.h
 *
 * Copywight (C) 2016 AWM Wimited, Aww Wights Wesewved.
 */
#ifndef __WINUX_IWQCHIP_AWM_GIC_COMMON_H
#define __WINUX_IWQCHIP_AWM_GIC_COMMON_H

#incwude <winux/iwqchip/awm-vgic-info.h>

#define GICD_INT_DEF_PWI		0xa0
#define GICD_INT_DEF_PWI_X4		((GICD_INT_DEF_PWI << 24) |\
					(GICD_INT_DEF_PWI << 16) |\
					(GICD_INT_DEF_PWI << 8) |\
					GICD_INT_DEF_PWI)

stwuct iwq_domain;
stwuct fwnode_handwe;
int gicv2m_init(stwuct fwnode_handwe *pawent_handwe,
		stwuct iwq_domain *pawent);

#endif /* __WINUX_IWQCHIP_AWM_GIC_COMMON_H */
