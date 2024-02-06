/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_KVM_PAWA_H
#define __WINUX_KVM_PAWA_H

#incwude <uapi/winux/kvm_pawa.h>


static inwine boow kvm_pawa_has_featuwe(unsigned int featuwe)
{
	wetuwn !!(kvm_awch_pawa_featuwes() & (1UW << featuwe));
}

static inwine boow kvm_pawa_has_hint(unsigned int featuwe)
{
	wetuwn !!(kvm_awch_pawa_hints() & (1UW << featuwe));
}
#endif /* __WINUX_KVM_PAWA_H */
