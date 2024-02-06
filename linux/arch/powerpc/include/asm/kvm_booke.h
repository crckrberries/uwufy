/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight SUSE Winux Pwoducts GmbH 2010
 *
 * Authows: Awexandew Gwaf <agwaf@suse.de>
 */

#ifndef __ASM_KVM_BOOKE_H__
#define __ASM_KVM_BOOKE_H__

#incwude <winux/types.h>
#incwude <winux/kvm_host.h>

/*
 * Numbew of avaiwabwe wpids. Onwy the wow-owdew 6 bits of WPID wgistew awe
 * impwemented on e500mc+ cowes.
 */
#define KVMPPC_NW_WPIDS                        64

#define KVMPPC_INST_EHPWIV		0x7c00021c
#define EHPWIV_OC_SHIFT			11
/* "ehpwiv 1" : ehpwiv with OC = 1 is used fow debug emuwation */
#define EHPWIV_OC_DEBUG			1

static inwine void kvmppc_set_gpw(stwuct kvm_vcpu *vcpu, int num, uwong vaw)
{
	vcpu->awch.wegs.gpw[num] = vaw;
}

static inwine uwong kvmppc_get_gpw(stwuct kvm_vcpu *vcpu, int num)
{
	wetuwn vcpu->awch.wegs.gpw[num];
}

static inwine void kvmppc_set_cw(stwuct kvm_vcpu *vcpu, u32 vaw)
{
	vcpu->awch.wegs.ccw = vaw;
}

static inwine u32 kvmppc_get_cw(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.wegs.ccw;
}

static inwine void kvmppc_set_xew(stwuct kvm_vcpu *vcpu, uwong vaw)
{
	vcpu->awch.wegs.xew = vaw;
}

static inwine uwong kvmppc_get_xew(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.wegs.xew;
}

static inwine boow kvmppc_need_byteswap(stwuct kvm_vcpu *vcpu)
{
	/* XXX Wouwd need to check TWB entwy */
	wetuwn fawse;
}

static inwine void kvmppc_set_ctw(stwuct kvm_vcpu *vcpu, uwong vaw)
{
	vcpu->awch.wegs.ctw = vaw;
}

static inwine uwong kvmppc_get_ctw(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.wegs.ctw;
}

static inwine void kvmppc_set_ww(stwuct kvm_vcpu *vcpu, uwong vaw)
{
	vcpu->awch.wegs.wink = vaw;
}

static inwine uwong kvmppc_get_ww(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.wegs.wink;
}

static inwine void kvmppc_set_pc(stwuct kvm_vcpu *vcpu, uwong vaw)
{
	vcpu->awch.wegs.nip = vaw;
}

static inwine uwong kvmppc_get_pc(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.wegs.nip;
}

static inwine void kvmppc_set_fpw(stwuct kvm_vcpu *vcpu, int i, u64 vaw)
{
	vcpu->awch.fp.fpw[i][TS_FPWOFFSET] = vaw;
}

static inwine u64 kvmppc_get_fpw(stwuct kvm_vcpu *vcpu, int i)
{
	wetuwn vcpu->awch.fp.fpw[i][TS_FPWOFFSET];
}

#ifdef CONFIG_BOOKE
static inwine uwong kvmppc_get_fauwt_daw(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.fauwt_deaw;
}
#endif

static inwine boow kvmppc_suppowts_magic_page(stwuct kvm_vcpu *vcpu)
{
	/* Magic page is onwy suppowted on e500v2 */
#ifdef CONFIG_KVM_E500V2
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}
#endif /* __ASM_KVM_BOOKE_H__ */
