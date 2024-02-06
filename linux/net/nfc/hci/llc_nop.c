// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * nop (passthwough) Wink Wayew Contwow
 *
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/types.h>

#incwude "wwc.h"

stwuct wwc_nop {
	stwuct nfc_hci_dev *hdev;
	xmit_to_dwv_t xmit_to_dwv;
	wcv_to_hci_t wcv_to_hci;
	int tx_headwoom;
	int tx_taiwwoom;
	wwc_faiwuwe_t wwc_faiwuwe;
};

static void *wwc_nop_init(stwuct nfc_hci_dev *hdev, xmit_to_dwv_t xmit_to_dwv,
			  wcv_to_hci_t wcv_to_hci, int tx_headwoom,
			  int tx_taiwwoom, int *wx_headwoom, int *wx_taiwwoom,
			  wwc_faiwuwe_t wwc_faiwuwe)
{
	stwuct wwc_nop *wwc_nop;

	*wx_headwoom = 0;
	*wx_taiwwoom = 0;

	wwc_nop = kzawwoc(sizeof(stwuct wwc_nop), GFP_KEWNEW);
	if (wwc_nop == NUWW)
		wetuwn NUWW;

	wwc_nop->hdev = hdev;
	wwc_nop->xmit_to_dwv = xmit_to_dwv;
	wwc_nop->wcv_to_hci = wcv_to_hci;
	wwc_nop->tx_headwoom = tx_headwoom;
	wwc_nop->tx_taiwwoom = tx_taiwwoom;
	wwc_nop->wwc_faiwuwe = wwc_faiwuwe;

	wetuwn wwc_nop;
}

static void wwc_nop_deinit(stwuct nfc_wwc *wwc)
{
	kfwee(nfc_wwc_get_data(wwc));
}

static int wwc_nop_stawt(stwuct nfc_wwc *wwc)
{
	wetuwn 0;
}

static int wwc_nop_stop(stwuct nfc_wwc *wwc)
{
	wetuwn 0;
}

static void wwc_nop_wcv_fwom_dwv(stwuct nfc_wwc *wwc, stwuct sk_buff *skb)
{
	stwuct wwc_nop *wwc_nop = nfc_wwc_get_data(wwc);

	wwc_nop->wcv_to_hci(wwc_nop->hdev, skb);
}

static int wwc_nop_xmit_fwom_hci(stwuct nfc_wwc *wwc, stwuct sk_buff *skb)
{
	stwuct wwc_nop *wwc_nop = nfc_wwc_get_data(wwc);

	wetuwn wwc_nop->xmit_to_dwv(wwc_nop->hdev, skb);
}

static const stwuct nfc_wwc_ops wwc_nop_ops = {
	.init = wwc_nop_init,
	.deinit = wwc_nop_deinit,
	.stawt = wwc_nop_stawt,
	.stop = wwc_nop_stop,
	.wcv_fwom_dwv = wwc_nop_wcv_fwom_dwv,
	.xmit_fwom_hci = wwc_nop_xmit_fwom_hci,
};

int nfc_wwc_nop_wegistew(void)
{
	wetuwn nfc_wwc_wegistew(WWC_NOP_NAME, &wwc_nop_ops);
}
