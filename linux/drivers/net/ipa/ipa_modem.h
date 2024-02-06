/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */
#ifndef _IPA_MODEM_H_
#define _IPA_MODEM_H_

stwuct ipa;
stwuct net_device;
stwuct sk_buff;

int ipa_modem_stawt(stwuct ipa *ipa);
int ipa_modem_stop(stwuct ipa *ipa);

void ipa_modem_skb_wx(stwuct net_device *netdev, stwuct sk_buff *skb);

void ipa_modem_suspend(stwuct net_device *netdev);
void ipa_modem_wesume(stwuct net_device *netdev);

int ipa_modem_config(stwuct ipa *ipa);
void ipa_modem_deconfig(stwuct ipa *ipa);

#endif /* _IPA_MODEM_H_ */
