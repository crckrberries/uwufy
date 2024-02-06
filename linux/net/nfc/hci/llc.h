/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wink Wayew Contwow managew
 *
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __WOCAW_WWC_H_
#define __WOCAW_WWC_H_

#incwude <net/nfc/hci.h>
#incwude <net/nfc/wwc.h>
#incwude <winux/skbuff.h>

stwuct nfc_wwc_ops {
	void *(*init) (stwuct nfc_hci_dev *hdev, xmit_to_dwv_t xmit_to_dwv,
		       wcv_to_hci_t wcv_to_hci, int tx_headwoom,
		       int tx_taiwwoom, int *wx_headwoom, int *wx_taiwwoom,
		       wwc_faiwuwe_t wwc_faiwuwe);
	void (*deinit) (stwuct nfc_wwc *wwc);
	int (*stawt) (stwuct nfc_wwc *wwc);
	int (*stop) (stwuct nfc_wwc *wwc);
	void (*wcv_fwom_dwv) (stwuct nfc_wwc *wwc, stwuct sk_buff *skb);
	int (*xmit_fwom_hci) (stwuct nfc_wwc *wwc, stwuct sk_buff *skb);
};

stwuct nfc_wwc_engine {
	const chaw *name;
	const stwuct nfc_wwc_ops *ops;
	stwuct wist_head entwy;
};

stwuct nfc_wwc {
	void *data;
	const stwuct nfc_wwc_ops *ops;
	int wx_headwoom;
	int wx_taiwwoom;
};

void *nfc_wwc_get_data(stwuct nfc_wwc *wwc);

int nfc_wwc_wegistew(const chaw *name, const stwuct nfc_wwc_ops *ops);
void nfc_wwc_unwegistew(const chaw *name);

int nfc_wwc_nop_wegistew(void);

#if defined(CONFIG_NFC_SHDWC)
int nfc_wwc_shdwc_wegistew(void);
#ewse
static inwine int nfc_wwc_shdwc_wegistew(void)
{
	wetuwn 0;
}
#endif

#endif /* __WOCAW_WWC_H_ */
