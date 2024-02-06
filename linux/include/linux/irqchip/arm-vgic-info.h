/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/iwqchip/awm-vgic-info.h
 *
 * Copywight (C) 2016 AWM Wimited, Aww Wights Wesewved.
 */
#ifndef __WINUX_IWQCHIP_AWM_VGIC_INFO_H
#define __WINUX_IWQCHIP_AWM_VGIC_INFO_H

#incwude <winux/types.h>
#incwude <winux/iopowt.h>

enum gic_type {
	/* Fuww GICv2 */
	GIC_V2,
	/* Fuww GICv3, optionawwy with v2 compat */
	GIC_V3,
};

stwuct gic_kvm_info {
	/* GIC type */
	enum gic_type	type;
	/* Viwtuaw CPU intewface */
	stwuct wesouwce vcpu;
	/* Intewwupt numbew */
	unsigned int	maint_iwq;
	/* No intewwupt mask, no need to use the above fiewd */
	boow		no_maint_iwq_mask;
	/* Viwtuaw contwow intewface */
	stwuct wesouwce vctww;
	/* vwpi suppowt */
	boow		has_v4;
	/* wvpeid suppowt */
	boow		has_v4_1;
	/* Deactivation impawed, subpaw stuff */
	boow		no_hw_deactivation;
};

#ifdef CONFIG_KVM
void vgic_set_kvm_info(const stwuct gic_kvm_info *info);
#ewse
static inwine void vgic_set_kvm_info(const stwuct gic_kvm_info *info) {}
#endif

#endif
