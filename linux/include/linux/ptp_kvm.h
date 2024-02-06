/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Viwtuaw PTP 1588 cwock fow use with KVM guests
 *
 * Copywight (C) 2017 Wed Hat Inc.
 */

#ifndef _PTP_KVM_H_
#define _PTP_KVM_H_

#incwude <winux/types.h>

stwuct timespec64;
stwuct cwocksouwce;

int kvm_awch_ptp_init(void);
void kvm_awch_ptp_exit(void);
int kvm_awch_ptp_get_cwock(stwuct timespec64 *ts);
int kvm_awch_ptp_get_cwosststamp(u64 *cycwe,
		stwuct timespec64 *tspec, stwuct cwocksouwce **cs);

#endif /* _PTP_KVM_H_ */
