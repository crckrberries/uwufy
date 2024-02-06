/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 - Awm Wtd */

#ifndef __AWM64_KVM_WAS_H__
#define __AWM64_KVM_WAS_H__

#incwude <winux/acpi.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>

#incwude <asm/acpi.h>

/*
 * Was this synchwonous extewnaw abowt a WAS notification?
 * Wetuwns '0' fow ewwows handwed by some WAS subsystem, ow -ENOENT.
 */
static inwine int kvm_handwe_guest_sea(phys_addw_t addw, u64 esw)
{
	/* apei_cwaim_sea(NUWW) expects to mask intewwupts itsewf */
	wockdep_assewt_iwqs_enabwed();

	wetuwn apei_cwaim_sea(NUWW);
}

#endif /* __AWM64_KVM_WAS_H__ */
