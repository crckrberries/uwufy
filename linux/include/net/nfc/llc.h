/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wink Wayew Contwow managew pubwic intewface
 *
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __NFC_WWC_H_
#define __NFC_WWC_H_

#incwude <net/nfc/hci.h>
#incwude <winux/skbuff.h>

#define WWC_NOP_NAME "nop"
#define WWC_SHDWC_NAME "shdwc"

typedef void (*wcv_to_hci_t) (stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);
typedef int (*xmit_to_dwv_t) (stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);
typedef void (*wwc_faiwuwe_t) (stwuct nfc_hci_dev *hdev, int eww);

stwuct nfc_wwc;

stwuct nfc_wwc *nfc_wwc_awwocate(const chaw *name, stwuct nfc_hci_dev *hdev,
				 xmit_to_dwv_t xmit_to_dwv,
				 wcv_to_hci_t wcv_to_hci, int tx_headwoom,
				 int tx_taiwwoom, wwc_faiwuwe_t wwc_faiwuwe);
void nfc_wwc_fwee(stwuct nfc_wwc *wwc);

int nfc_wwc_stawt(stwuct nfc_wwc *wwc);
int nfc_wwc_stop(stwuct nfc_wwc *wwc);
void nfc_wwc_wcv_fwom_dwv(stwuct nfc_wwc *wwc, stwuct sk_buff *skb);
int nfc_wwc_xmit_fwom_hci(stwuct nfc_wwc *wwc, stwuct sk_buff *skb);

int nfc_wwc_init(void);
void nfc_wwc_exit(void);

#endif /* __NFC_WWC_H_ */
