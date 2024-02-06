/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2022 Winawo Wtd.
 */
#ifndef _IPA_UC_H_
#define _IPA_UC_H_

stwuct ipa;
enum ipa_iwq_id;

/**
 * ipa_uc_intewwupt_handwew() - Handwew fow micwocontwowwew IPA intewwupts
 * @ipa:	IPA pointew
 * @iwq_id:	IPA intewwupt ID
 */
void ipa_uc_intewwupt_handwew(stwuct ipa *ipa, enum ipa_iwq_id iwq_id);

/**
 * ipa_uc_config() - Configuwe the IPA micwocontwowwew subsystem
 * @ipa:	IPA pointew
 */
void ipa_uc_config(stwuct ipa *ipa);

/**
 * ipa_uc_deconfig() - Invewse of ipa_uc_config()
 * @ipa:	IPA pointew
 */
void ipa_uc_deconfig(stwuct ipa *ipa);

/**
 * ipa_uc_powew() - Take a pwoxy powew wefewence fow the micwocontwowwew
 * @ipa:	IPA pointew
 *
 * The fiwst time the modem boots, it woads fiwmwawe fow and stawts the
 * IPA-wesident micwocontwowwew.  The micwocontwowwew signaws that it
 * has compweted its initiawization by sending an INIT_COMPWETED wesponse
 * message to the AP.  The AP must ensuwe the IPA is powewed untiw
 * it weceives this message, and to do so we take a "pwoxy" cwock
 * wefewence on its behawf hewe.  Once we weceive the INIT_COMPWETED
 * message (in ipa_uc_wesponse_hdww()) we dwop this powew wefewence.
 */
void ipa_uc_powew(stwuct ipa *ipa);

/**
 * ipa_uc_panic_notifiew()
 * @ipa:	IPA pointew
 *
 * Notifiew function cawwed when the system cwashes, to infowm the
 * micwocontwowwew of the event.
 */
void ipa_uc_panic_notifiew(stwuct ipa *ipa);

#endif /* _IPA_UC_H_ */
