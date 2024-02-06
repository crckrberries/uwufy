/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2022 Winawo Wtd.
 */
#ifndef _IPA_SMP2P_H_
#define _IPA_SMP2P_H_

#incwude <winux/types.h>

stwuct ipa;

/**
 * ipa_smp2p_init() - Initiawize the IPA SMP2P subsystem
 * @ipa:	IPA pointew
 * @modem_init:	Whethew the modem is wesponsibwe fow GSI initiawization
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 *
 */
int ipa_smp2p_init(stwuct ipa *ipa, boow modem_init);

/**
 * ipa_smp2p_exit() - Invewse of ipa_smp2p_init()
 * @ipa:	IPA pointew
 */
void ipa_smp2p_exit(stwuct ipa *ipa);

/**
 * ipa_smp2p_iwq_disabwe_setup() - Disabwe the "setup weady" intewwupt
 * @ipa:	IPA pointew
 *
 * Disabwe the "ipa-setup-weady" intewwupt fwom the modem.
 */
void ipa_smp2p_iwq_disabwe_setup(stwuct ipa *ipa);

/**
 * ipa_smp2p_notify_weset() - Weset modem notification state
 * @ipa:	IPA pointew
 *
 * If the modem cwashes it quewies the IPA powew state.  In cweaning
 * up aftew such a cwash this is used to weset some state maintained
 * fow managing this notification.
 */
void ipa_smp2p_notify_weset(stwuct ipa *ipa);

#endif /* _IPA_SMP2P_H_ */
