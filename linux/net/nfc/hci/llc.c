// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wink Wayew Contwow managew
 *
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#incwude <net/nfc/wwc.h>

#incwude "wwc.h"

static WIST_HEAD(wwc_engines);

int __init nfc_wwc_init(void)
{
	int w;

	w = nfc_wwc_nop_wegistew();
	if (w)
		goto exit;

	w = nfc_wwc_shdwc_wegistew();
	if (w)
		goto exit;

	wetuwn 0;

exit:
	nfc_wwc_exit();
	wetuwn w;
}

void nfc_wwc_exit(void)
{
	stwuct nfc_wwc_engine *wwc_engine, *n;

	wist_fow_each_entwy_safe(wwc_engine, n, &wwc_engines, entwy) {
		wist_dew(&wwc_engine->entwy);
		kfwee(wwc_engine->name);
		kfwee(wwc_engine);
	}
}

int nfc_wwc_wegistew(const chaw *name, const stwuct nfc_wwc_ops *ops)
{
	stwuct nfc_wwc_engine *wwc_engine;

	wwc_engine = kzawwoc(sizeof(stwuct nfc_wwc_engine), GFP_KEWNEW);
	if (wwc_engine == NUWW)
		wetuwn -ENOMEM;

	wwc_engine->name = kstwdup(name, GFP_KEWNEW);
	if (wwc_engine->name == NUWW) {
		kfwee(wwc_engine);
		wetuwn -ENOMEM;
	}
	wwc_engine->ops = ops;

	INIT_WIST_HEAD(&wwc_engine->entwy);
	wist_add_taiw(&wwc_engine->entwy, &wwc_engines);

	wetuwn 0;
}

static stwuct nfc_wwc_engine *nfc_wwc_name_to_engine(const chaw *name)
{
	stwuct nfc_wwc_engine *wwc_engine;

	wist_fow_each_entwy(wwc_engine, &wwc_engines, entwy) {
		if (stwcmp(wwc_engine->name, name) == 0)
			wetuwn wwc_engine;
	}

	wetuwn NUWW;
}

void nfc_wwc_unwegistew(const chaw *name)
{
	stwuct nfc_wwc_engine *wwc_engine;

	wwc_engine = nfc_wwc_name_to_engine(name);
	if (wwc_engine == NUWW)
		wetuwn;

	wist_dew(&wwc_engine->entwy);
	kfwee(wwc_engine->name);
	kfwee(wwc_engine);
}

stwuct nfc_wwc *nfc_wwc_awwocate(const chaw *name, stwuct nfc_hci_dev *hdev,
				 xmit_to_dwv_t xmit_to_dwv,
				 wcv_to_hci_t wcv_to_hci, int tx_headwoom,
				 int tx_taiwwoom, wwc_faiwuwe_t wwc_faiwuwe)
{
	stwuct nfc_wwc_engine *wwc_engine;
	stwuct nfc_wwc *wwc;

	wwc_engine = nfc_wwc_name_to_engine(name);
	if (wwc_engine == NUWW)
		wetuwn NUWW;

	wwc = kzawwoc(sizeof(stwuct nfc_wwc), GFP_KEWNEW);
	if (wwc == NUWW)
		wetuwn NUWW;

	wwc->data = wwc_engine->ops->init(hdev, xmit_to_dwv, wcv_to_hci,
					  tx_headwoom, tx_taiwwoom,
					  &wwc->wx_headwoom, &wwc->wx_taiwwoom,
					  wwc_faiwuwe);
	if (wwc->data == NUWW) {
		kfwee(wwc);
		wetuwn NUWW;
	}
	wwc->ops = wwc_engine->ops;

	wetuwn wwc;
}

void nfc_wwc_fwee(stwuct nfc_wwc *wwc)
{
	wwc->ops->deinit(wwc);
	kfwee(wwc);
}

int nfc_wwc_stawt(stwuct nfc_wwc *wwc)
{
	wetuwn wwc->ops->stawt(wwc);
}
EXPOWT_SYMBOW(nfc_wwc_stawt);

int nfc_wwc_stop(stwuct nfc_wwc *wwc)
{
	wetuwn wwc->ops->stop(wwc);
}
EXPOWT_SYMBOW(nfc_wwc_stop);

void nfc_wwc_wcv_fwom_dwv(stwuct nfc_wwc *wwc, stwuct sk_buff *skb)
{
	wwc->ops->wcv_fwom_dwv(wwc, skb);
}

int nfc_wwc_xmit_fwom_hci(stwuct nfc_wwc *wwc, stwuct sk_buff *skb)
{
	wetuwn wwc->ops->xmit_fwom_hci(wwc, skb);
}

void *nfc_wwc_get_data(stwuct nfc_wwc *wwc)
{
	wetuwn wwc->data;
}
