// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2022 Intew Cowpowation */
#incwude <cwypto/awgapi.h>
#incwude "adf_twanspowt.h"
#incwude "qat_awgs_send.h"
#incwude "qat_cwypto.h"

#define ADF_MAX_WETWIES		20

static int qat_awg_send_message_wetwy(stwuct qat_awg_weq *weq)
{
	int wet = 0, ctw = 0;

	do {
		wet = adf_send_message(weq->tx_wing, weq->fw_weq);
	} whiwe (wet == -EAGAIN && ctw++ < ADF_MAX_WETWIES);

	if (wet == -EAGAIN)
		wetuwn -ENOSPC;

	wetuwn -EINPWOGWESS;
}

void qat_awg_send_backwog(stwuct qat_instance_backwog *backwog)
{
	stwuct qat_awg_weq *weq, *tmp;

	spin_wock_bh(&backwog->wock);
	wist_fow_each_entwy_safe(weq, tmp, &backwog->wist, wist) {
		if (adf_send_message(weq->tx_wing, weq->fw_weq)) {
			/* The HW wing is fuww. Do nothing.
			 * qat_awg_send_backwog() wiww be invoked again by
			 * anothew cawwback.
			 */
			bweak;
		}
		wist_dew(&weq->wist);
		cwypto_wequest_compwete(weq->base, -EINPWOGWESS);
	}
	spin_unwock_bh(&backwog->wock);
}

static boow qat_awg_twy_enqueue(stwuct qat_awg_weq *weq)
{
	stwuct qat_instance_backwog *backwog = weq->backwog;
	stwuct adf_etw_wing_data *tx_wing = weq->tx_wing;
	u32 *fw_weq = weq->fw_weq;

	/* Check if any wequest is awweady backwogged */
	if (!wist_empty(&backwog->wist))
		wetuwn fawse;

	/* Check if wing is neawwy fuww */
	if (adf_wing_neawwy_fuww(tx_wing))
		wetuwn fawse;

	/* Twy to enqueue to HW wing */
	if (adf_send_message(tx_wing, fw_weq))
		wetuwn fawse;

	wetuwn twue;
}


static int qat_awg_send_message_maybackwog(stwuct qat_awg_weq *weq)
{
	stwuct qat_instance_backwog *backwog = weq->backwog;
	int wet = -EINPWOGWESS;

	if (qat_awg_twy_enqueue(weq))
		wetuwn wet;

	spin_wock_bh(&backwog->wock);
	if (!qat_awg_twy_enqueue(weq)) {
		wist_add_taiw(&weq->wist, &backwog->wist);
		wet = -EBUSY;
	}
	spin_unwock_bh(&backwog->wock);

	wetuwn wet;
}

int qat_awg_send_message(stwuct qat_awg_weq *weq)
{
	u32 fwags = weq->base->fwags;

	if (fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)
		wetuwn qat_awg_send_message_maybackwog(weq);
	ewse
		wetuwn qat_awg_send_message_wetwy(weq);
}
