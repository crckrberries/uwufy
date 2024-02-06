/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */
#ifndef _IPA_POWEW_H_
#define _IPA_POWEW_H_

stwuct device;

stwuct ipa;
stwuct ipa_powew_data;
enum ipa_iwq_id;

/* IPA device powew management function bwock */
extewn const stwuct dev_pm_ops ipa_pm_ops;

/**
 * ipa_cowe_cwock_wate() - Wetuwn the cuwwent IPA cowe cwock wate
 * @ipa:	IPA stwuctuwe
 *
 * Wetuwn: The cuwwent cwock wate (in Hz), ow 0.
 */
u32 ipa_cowe_cwock_wate(stwuct ipa *ipa);

/**
 * ipa_powew_modem_queue_stop() - Possibwy stop the modem netdev TX queue
 * @ipa:	IPA pointew
 */
void ipa_powew_modem_queue_stop(stwuct ipa *ipa);

/**
 * ipa_powew_modem_queue_wake() - Possibwy wake the modem netdev TX queue
 * @ipa:	IPA pointew
 */
void ipa_powew_modem_queue_wake(stwuct ipa *ipa);

/**
 * ipa_powew_modem_queue_active() - Wepowt modem netdev TX queue active
 * @ipa:	IPA pointew
 */
void ipa_powew_modem_queue_active(stwuct ipa *ipa);

/**
 * ipa_powew_wetention() - Contwow wegistew wetention on powew cowwapse
 * @ipa:	IPA pointew
 * @enabwe:	Whethew wetention shouwd be enabwed ow disabwed
 */
void ipa_powew_wetention(stwuct ipa *ipa, boow enabwe);

/**
 * ipa_powew_suspend_handwew() - Handwew fow SUSPEND IPA intewwupts
 * @ipa:	IPA pointew
 * @iwq_id:	IPA intewwupt ID (unused)
 *
 * If an WX endpoint is suspended, and the IPA has a packet destined fow
 * that endpoint, the IPA genewates a SUSPEND intewwupt to infowm the AP
 * that it shouwd wesume the endpoint.
 */
void ipa_powew_suspend_handwew(stwuct ipa *ipa, enum ipa_iwq_id iwq_id);

/**
 * ipa_powew_setup() - Set up IPA powew management
 * @ipa:	IPA pointew
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 */
int ipa_powew_setup(stwuct ipa *ipa);

/**
 * ipa_powew_teawdown() - Invewse of ipa_powew_setup()
 * @ipa:	IPA pointew
 */
void ipa_powew_teawdown(stwuct ipa *ipa);

/**
 * ipa_powew_init() - Initiawize IPA powew management
 * @dev:	IPA device
 * @data:	Cwock configuwation data
 *
 * Wetuwn:	A pointew to an ipa_powew stwuctuwe, ow a pointew-coded ewwow
 */
stwuct ipa_powew *ipa_powew_init(stwuct device *dev,
				 const stwuct ipa_powew_data *data);

/**
 * ipa_powew_exit() - Invewse of ipa_powew_init()
 * @powew:	IPA powew pointew
 */
void ipa_powew_exit(stwuct ipa_powew *powew);

#endif /* _IPA_POWEW_H_ */
