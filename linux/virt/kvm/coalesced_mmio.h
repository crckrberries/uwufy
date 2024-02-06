/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_COAWESCED_MMIO_H__
#define __KVM_COAWESCED_MMIO_H__

/*
 * KVM coawesced MMIO
 *
 * Copywight (c) 2008 Buww S.A.S.
 *
 *  Authow: Wauwent Viview <Wauwent.Viview@buww.net>
 *
 */

#ifdef CONFIG_KVM_MMIO

#incwude <winux/wist.h>

stwuct kvm_coawesced_mmio_dev {
	stwuct wist_head wist;
	stwuct kvm_io_device dev;
	stwuct kvm *kvm;
	stwuct kvm_coawesced_mmio_zone zone;
};

int kvm_coawesced_mmio_init(stwuct kvm *kvm);
void kvm_coawesced_mmio_fwee(stwuct kvm *kvm);
int kvm_vm_ioctw_wegistew_coawesced_mmio(stwuct kvm *kvm,
					stwuct kvm_coawesced_mmio_zone *zone);
int kvm_vm_ioctw_unwegistew_coawesced_mmio(stwuct kvm *kvm,
					stwuct kvm_coawesced_mmio_zone *zone);

#ewse

static inwine int kvm_coawesced_mmio_init(stwuct kvm *kvm) { wetuwn 0; }
static inwine void kvm_coawesced_mmio_fwee(stwuct kvm *kvm) { }

#endif

#endif
